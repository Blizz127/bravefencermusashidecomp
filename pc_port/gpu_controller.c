#include "musashi_gpu_controller.h"
#include <stdio.h>
#include <stdlib.h>

#define GPU_RESET_READ_LATCH 0x400u
#define GPU_STATUS_BASE 0x00802000u
#define GPU_STATUS_DMA_REQUEST (1u << 25)
#define GPU_STATUS_READY_COMMAND (1u << 26)
#define GPU_STATUS_READY_DMA (1u << 28)
#define GPU_STATUS_VBLANK_PARITY (1u << 31)

/* PSX-SPX Quick Rectangle Fill and fill masking. Pinned PCSX command
 * parser is a state-machine aid; its clipping quirks are not reproduced. */
int musashi_gpu_fill_derive(MusashiGpuFill *fill) {
    uint32_t color;
    if (!fill || (fill->command >> 24) != 2u) return 0;
    color = fill->command;
    fill->x = (uint16_t)(fill->xy & 0x3f0u);
    fill->y = (uint16_t)((fill->xy >> 16) & 0x1ffu);
    fill->width = (uint16_t)(((fill->wh & 0x3ffu) + 15u) & ~15u);
    fill->height = (uint16_t)((fill->wh >> 16) & 0x1ffu);
    fill->color = (uint16_t)(((color >> 3) & 0x1fu) |
        ((color >> 6) & 0x3e0u) | ((color >> 9) & 0x7c00u));
    return 1;
}

static void discard_fill(MusashiGpuController *controller) {
    controller->fill_command = controller->fill_xy = 0;
    controller->fill_words = 0;
}

static void discard_store(MusashiGpuController *controller) {
    controller->store_command = controller->store_xy = controller->store_wh = 0;
    controller->store_x = controller->store_y = 0;
    controller->store_w = controller->store_h = 0;
    controller->store_px = controller->store_py = 0;
    controller->store_remaining = 0;
    controller->store_phase = 0;
}

static void discard_copy(MusashiGpuController *controller) {
    controller->copy_command = controller->copy_src = controller->copy_dst = 0;
    controller->copy_words = 0;
}

static void discard_prim(MusashiGpuController *controller) {
    unsigned i;
    controller->prim_needed = controller->prim_got = 0;
    for (i = 0; i < 12u; ++i) controller->prim_data[i] = 0;
}

static int backend_bound(const MusashiGpuController *controller) {
    return controller && controller->backend.reset &&
           controller->backend.draw_mode &&
           controller->backend.display_enable &&
           controller->backend.clear_fifo && controller->backend.ready;
}

static int enter_callback(MusashiGpuController *controller) {
    if (controller->executing) {
        controller->faulted = 1;
        return 0;
    }
    controller->executing = 1;
    return 1;
}

static int finish_callback(MusashiGpuController *controller, int accepted) {
    controller->executing = 0;
    if (!accepted) controller->faulted = 1;
    return accepted > 0;
}

static void display_reset_state(MusashiGpuController *controller);

static int backend_ready(MusashiGpuController *controller, int *ready) {
    int state;
    if (!backend_bound(controller) || !ready) return 0;
    if (!enter_callback(controller)) return 0;
    state = controller->backend.ready(controller->backend.userdata);
    if (!finish_callback(controller, state >= 0) || controller->faulted)
        return 0;
    *ready = state > 0;
    return 1;
}

static void reset_state(MusashiGpuController *controller) {
    controller->read_latch = GPU_RESET_READ_LATCH;
    controller->draw_mode = 0;
    controller->dma_direction = 0;
    controller->display_disabled = 1;
    controller->executing = 0;
    controller->vblank_parity = 0;
    controller->texture_window = 0;
    controller->drawing_area_start = 0;
    controller->drawing_area_end = 0;
    controller->drawing_offset = 0;
    controller->mask_flags = 0;
    display_reset_state(controller);
    discard_fill(controller);
    discard_store(controller);
    discard_copy(controller);
    discard_prim(controller);
}

static int backend_reset(MusashiGpuController *controller) {
    int accepted;
    if (!enter_callback(controller)) return 0;
    accepted = controller->backend.reset(controller->backend.userdata);
    return finish_callback(controller, accepted);
}

static int backend_draw_mode(MusashiGpuController *controller, uint32_t word) {
    int accepted;
    if (!enter_callback(controller)) return 0;
    accepted = controller->backend.draw_mode(controller->backend.userdata, word);
    return finish_callback(controller, accepted);
}

static int backend_display_enable(MusashiGpuController *controller, int enabled) {
    int accepted;
    if (!enter_callback(controller)) return 0;
    accepted = controller->backend.display_enable(
        controller->backend.userdata, enabled);
    return finish_callback(controller, accepted);
}

static int backend_clear_fifo(MusashiGpuController *controller) {
    int accepted;
    if (!enter_callback(controller)) return 0;
    accepted = controller->backend.clear_fifo(controller->backend.userdata);
    return finish_callback(controller, accepted);
}

static int backend_environment(MusashiGpuController *controller,
                               uint32_t word) {
    int accepted;
    if (!controller->backend.environment) return 0;
    if (!enter_callback(controller)) return 0;
    accepted = controller->backend.environment(
        controller->backend.userdata, word);
    return finish_callback(controller, accepted);
}

static int display_mode_divisor(uint32_t mode, uint8_t *divisor) {
    mode &= 0xffu;
    /* Bits 2/5 are 480-line and interlace; they do not change the dot clock.
     * PAL, 24-bit, and reverse remain refused. */
    if ((mode & 0x18u) != 0 || (mode & 0x80u) != 0 || !divisor)
        return 0;
    if ((mode & 0x40u) != 0) {
        if ((mode & 3u) != 0) return 0;
        *divisor = 7;
        return 1;
    }
    switch (mode & 3u) {
    case 0: *divisor = 10; return 1;
    case 1: *divisor = 8; return 1;
    case 2: *divisor = 5; return 1;
    case 3: *divisor = 4; return 1;
    default: return 0;
    }
}

int musashi_gpu_display_derive(MusashiGpuDisplayState *state) {
    uint8_t divisor;
    uint32_t width;
    uint32_t height;

    if (!state || !display_mode_divisor(state->mode, &divisor)) return 0;
    state->origin &= 0x0007ffffu;
    state->horizontal &= 0x00ffffffu;
    state->vertical &= 0x000fffffu;
    state->mode &= 0x000000ffu;
    state->x = (uint16_t)(state->origin & 0x3ffu);
    state->y = (uint16_t)((state->origin >> 10) & 0x1ffu);
    state->h_start = (uint16_t)(state->horizontal & 0xfffu);
    state->h_end = (uint16_t)((state->horizontal >> 12) & 0xfffu);
    state->v_start = (uint16_t)(state->vertical & 0x3ffu);
    state->v_end = (uint16_t)((state->vertical >> 10) & 0x3ffu);
    if (state->h_end <= state->h_start || state->v_end <= state->v_start)
        return 0;
    if (state->v_start != 16 || state->v_end != 256) return 0;
    width = (((uint32_t)state->h_end - state->h_start) / divisor + 2u) & ~3u;
    height = (uint32_t)state->v_end - state->v_start;
    /* GP1(08) bits2+5 select 480-line interlaced scanout. The vertical
     * range counts scanlines per field; the host presents both fields. */
    if ((state->mode & 0x24u) == 0x24u) height *= 2u;
    if (width == 0 || width > 1024 || height == 0 || height > 512)
        return 0;
    state->dot_divisor = divisor;
    state->width = (uint16_t)width;
    state->height = (uint16_t)height;
    return 1;
}

static void display_reset_state(MusashiGpuController *controller) {
    controller->display.origin = 0;
    controller->display.horizontal = 0x00c00200u;
    controller->display.vertical = 0x00040010u;
    controller->display.mode = 0;
    (void)musashi_gpu_display_derive(&controller->display);
}

static int backend_display(MusashiGpuController *controller,
                           const MusashiGpuDisplayState *candidate) {
    int accepted;
    if (!controller->backend.display || !candidate ||
        !enter_callback(controller)) return 0;
    accepted = controller->backend.display(controller->backend.userdata,
                                           candidate);
    return finish_callback(controller, accepted);
}

static int display_commit(MusashiGpuController *controller,
                          MusashiGpuDisplayState *candidate) {
    int ready;
    if (!controller->backend.display || !musashi_gpu_display_derive(candidate)) return 0;
    if (!backend_ready(controller, &ready) || !ready) return 0;
    if (!backend_display(controller, candidate)) return 0;
    controller->display = *candidate;
    return controller->faulted ? 0 : 1;
}

static int display_write(MusashiGpuController *controller, uint32_t opcode,
                         uint32_t value) {
    MusashiGpuDisplayState candidate;
    if (!controller->backend.display) return 0;
    candidate = controller->display;
    switch (opcode) {
    case 0x05u: candidate.origin = value & 0x0007ffffu; break;
    case 0x06u: candidate.horizontal = value & 0x00ffffffu; break;
    case 0x07u: candidate.vertical = value & 0x000fffffu; break;
    case 0x08u: candidate.mode = value & 0x000000ffu; break;
    default: return 0;
    }
    return display_commit(controller, &candidate);
}

int musashi_gpu_controller_init(MusashiGpuController *controller,
                                const MusashiGpuBackend *backend) {
    MusashiGpuBackend selected;
    int accepted;

    if (!controller || !backend || !backend->reset || !backend->draw_mode ||
        !backend->display_enable || !backend->clear_fifo || !backend->ready)
        return 0;
    if (controller->executing) {
        controller->faulted = 1;
        return 0;
    }
    selected = *backend;
    /* Reserve the instance while the external reset callback runs. A nested
     * init or MMIO operation therefore becomes a detected reentry fault and
     * cannot publish a half-initialized backend. */
    controller->executing = 1;
    controller->faulted = 0;
    accepted = selected.reset(selected.userdata);
    if (!accepted || controller->faulted) {
        int reentered = controller->faulted;
        controller->executing = 0;
        controller->faulted = reentered ? 1 : 0;
        return 0;
    }
    controller->backend = selected;
    controller->faulted = 0;
    reset_state(controller);
    controller->accepted_gp0_words = 0;
    controller->stored_pixels = 0;
    discard_store(controller);
    return 1;
}

static uint32_t status_word(const MusashiGpuController *controller, int ready) {
    uint32_t status = GPU_STATUS_BASE;
    uint32_t dma_request = 0;

    status &= ~0x00800000u;
    if (controller->display_disabled) status |= 0x00800000u;
    status = (status & ~0x7ffu) | (controller->draw_mode & 0x7ffu);
    if (controller->draw_mode & 0x800u) status |= 0x8000u;
    status &= ~((1u << 14) | (1u << 16) | (7u << 17) | (0xfu << 19));
    status |= (controller->display.mode & 0x40u) ? (1u << 16) : 0u;
    status |= (controller->display.mode & 3u) << 17;
    status |= ((controller->display.mode >> 2) & 0xfu) << 19;
    status &= ~((1u << 11) | (1u << 12));
    status |= (controller->mask_flags & 3u) << 11;
    status = (status & ~(3u << 29)) |
             ((controller->dma_direction & 3u) << 29);
    if (!controller->executing && ready) {
        status |= GPU_STATUS_READY_DMA;
        if (!controller->fill_words && !controller->store_phase &&
            !controller->prim_needed && !controller->copy_words)
            status |= GPU_STATUS_READY_COMMAND;
    }
    if (controller->dma_direction == 1u)
        dma_request = (uint32_t)ready;
    else if (controller->dma_direction == 2u)
        dma_request = (!controller->executing && ready) ? 1u : 0u;
    if (dma_request) status |= GPU_STATUS_DMA_REQUEST;
    if (controller->vblank_parity) status |= GPU_STATUS_VBLANK_PARITY;
    return status;
}

int musashi_gpu_controller_vblank(MusashiGpuController *controller) {
    int ready;

    if (!controller) return 0;
    if (controller->executing) {
        controller->faulted = 1;
        return 0;
    }
    if (!backend_bound(controller) || controller->faulted) return 0;
    if (!backend_ready(controller, &ready)) return 0;
    (void)ready;
    controller->vblank_parity ^= 1u;
    return 1;
}

int musashi_gpu_controller_read32(MusashiGpuController *controller,
                                   uint32_t address, uint32_t *value) {
    int ready;

    if (!controller || !value) return 0;
    if (controller->executing) {
        controller->faulted = 1;
        return 0;
    }
    if (!backend_bound(controller) || controller->faulted) return 0;
    if (address == MUSASHI_GPU_GPUREAD) {
        *value = controller->read_latch;
        return 1;
    }
    if (address != MUSASHI_GPU_GPUSTAT) return 0;
    if (!backend_ready(controller, &ready)) return 0;
    *value = status_word(controller, ready);
    return 1;
}

static int fill_word(MusashiGpuController *controller, uint32_t word) {
    MusashiGpuFill fill = {0};
    uint64_t pixels;
    int ready, accepted;
    if (!controller->backend.fill_vram || controller->fill_words > 2u ||
        controller->accepted_gp0_words == UINT64_MAX) return 0;
    if (controller->fill_words == 2u) {
        fill.command = controller->fill_command;
        fill.xy = controller->fill_xy;
        fill.wh = word;
        if (!musashi_gpu_fill_derive(&fill)) return 0;
        pixels = (uint64_t)fill.width * fill.height;
        if (controller->completed_fills == UINT64_MAX ||
            controller->filled_pixels > UINT64_MAX - pixels) return 0;
    } else pixels = 0;
    if (!backend_ready(controller, &ready) || !ready) return 0;
    if (controller->fill_words == 0u) {
        controller->fill_command = word;
        controller->fill_words = 1;
    } else if (controller->fill_words == 1u) {
        controller->fill_xy = word;
        controller->fill_words = 2;
    } else {
        if (!enter_callback(controller)) return 0;
        accepted = controller->backend.fill_vram(controller->backend.userdata, &fill);
        if (!finish_callback(controller, accepted)) return 0;
        /* Backend acceptance is an effect even when a nested operation has
         * faulted the controller. DMA observes the monotonic accepted count. */
        controller->last_fill = fill;
        controller->completed_fills++;
        controller->filled_pixels += pixels;
        discard_fill(controller);
    }
    controller->accepted_gp0_words++;
    return controller->faulted ? 0 : 1;
}

static int store_word(MusashiGpuController *controller, uint32_t word) {
    uint16_t pixels[2];
    unsigned count, i;
    int ready;
    if (!controller->backend.store_vram ||
        controller->accepted_gp0_words == UINT64_MAX) return 0;
    if (controller->store_phase == 0) {
        if ((word >> 24) != 0xa0u) return 0;
        controller->store_command = word;
        controller->store_phase = 1;
        controller->accepted_gp0_words++;
        return controller->faulted ? 0 : 1;
    }
    if (controller->store_phase == 1) {
        controller->store_xy = word;
        controller->store_phase = 2;
        controller->accepted_gp0_words++;
        return controller->faulted ? 0 : 1;
    }
    if (controller->store_phase == 2) {
        uint32_t width = word & 0xffffu;
        uint32_t height = word >> 16;
        if (!width) width = 1024u;
        if (!height) height = 512u;
        if (width > 1024u || height > 512u) return 0;
        controller->store_wh = word;
        controller->store_x = (uint16_t)(controller->store_xy & 0x3ffu);
        controller->store_y = (uint16_t)((controller->store_xy >> 16) & 0x1ffu);
        controller->store_w = (uint16_t)width;
        controller->store_h = (uint16_t)height;
        controller->store_px = controller->store_py = 0;
        controller->store_remaining = width * height;
        controller->store_phase = 3;
        controller->accepted_gp0_words++;
        if (!controller->store_remaining) discard_store(controller);
        return controller->faulted ? 0 : 1;
    }
    if (controller->store_phase != 3 || !controller->store_remaining) return 0;
    if (!backend_ready(controller, &ready) || !ready) return 0;
    pixels[0] = (uint16_t)word;
    pixels[1] = (uint16_t)(word >> 16);
    count = controller->store_remaining >= 2u ? 2u : 1u;
    for (i = 0; i < count; ++i) {
        uint16_t x = (uint16_t)((controller->store_x + controller->store_px) & 1023u);
        uint16_t y = (uint16_t)((controller->store_y + controller->store_py) & 511u);
        if (!enter_callback(controller)) return 0;
        if (!finish_callback(controller,
                controller->backend.store_vram(controller->backend.userdata,
                                               x, y, pixels[i])))
            return 0;
        if (controller->stored_pixels == UINT64_MAX) return 0;
        controller->stored_pixels++;
        controller->store_remaining--;
        controller->store_px++;
        if (controller->store_px >= controller->store_w) {
            controller->store_px = 0;
            controller->store_py++;
        }
    }
    controller->accepted_gp0_words++;
    if (!controller->store_remaining) discard_store(controller);
    return controller->faulted ? 0 : 1;
}

/* Ordering follows DuckStation gpu_sw_rasterizer.inl CopyVRAMImpl:
 * rows advance, columns reverse for rightward copies. Its wrapped rectangle
 * split is an emulator reference, explicitly not console-verified there.
 * https://github.com/stenzek/duckstation/blob/master/src/core/gpu_sw_rasterizer.inl
 * PSX-SPX GPU Memory Transfer Commands supplies coordinate/size and mask rules.
 */
static int copy_rectangle(MusashiGpuController *c, unsigned sx, unsigned sy,
                          unsigned dx, unsigned dy, unsigned w, unsigned h) {
    unsigned row, step;
    for (row = 0; row < h; ++row) {
        for (step = 0; step < w; ++step) {
            unsigned col = sx < dx ? w - 1u - step : step;
            uint16_t pixel, destination;
            int accepted;
            if (!enter_callback(c)) return 0;
            accepted = c->backend.read_vram(c->backend.userdata,
                (uint16_t)(sx + col), (uint16_t)((sy + row) & 511u), &pixel);
            if (!finish_callback(c, accepted > 0) || c->faulted) return 0;
            if (c->mask_flags & 2u) {
                if (!enter_callback(c)) return 0;
                accepted = c->backend.read_vram(c->backend.userdata,
                    (uint16_t)(dx + col), (uint16_t)((dy + row) & 511u), &destination);
                if (!finish_callback(c, accepted > 0) || c->faulted) return 0;
                if (destination & 0x8000u) continue;
            }
            if (c->mask_flags & 1u) pixel |= 0x8000u;
            if (!enter_callback(c)) return 0;
            accepted = c->backend.store_vram(c->backend.userdata,
                (uint16_t)(dx + col), (uint16_t)((dy + row) & 511u), pixel);
            if (!finish_callback(c, accepted > 0)) return 0;
            c->copied_pixels++;
            if (c->faulted) return 0;
        }
    }
    return 1;
}

static int copy_word(MusashiGpuController *c, uint32_t word) {
    unsigned sx, sy, dx, dy, width, height, ry, rx;
    int ready;
    if (!c->backend.read_vram || !c->backend.store_vram ||
        c->accepted_gp0_words == UINT64_MAX) return 0;
    if (c->copy_words < 3u) {
        if (!c->copy_words) c->copy_command = word;
        else if (c->copy_words == 1u) c->copy_src = word;
        else c->copy_dst = word;
        c->copy_words++;
        c->accepted_gp0_words++;
        return 1;
    }
    width = ((word - 1u) & 1023u) + 1u;
    height = (((word >> 16) - 1u) & 511u) + 1u;
    if (c->completed_copies == UINT64_MAX ||
        c->copied_pixels > UINT64_MAX - (uint64_t)width * height) return 0;
    if (!backend_ready(c, &ready) || !ready) return 0;
    sx = c->copy_src & 1023u;
    sy = (c->copy_src >> 16) & 511u;
    dx = c->copy_dst & 1023u;
    dy = (c->copy_dst >> 16) & 511u;
    if (sx + width <= 1024u && dx + width <= 1024u) {
        if (!copy_rectangle(c, sx, sy, dx, dy, width, height)) return 0;
    } else {
        for (ry = 0; ry < height;) {
            unsigned ys = (sy + ry) & 511u, yd = (dy + ry) & 511u;
            unsigned rows = height - ry;
            if (rows > 512u - ys) rows = 512u - ys;
            if (rows > 512u - yd) rows = 512u - yd;
            for (rx = 0; rx < width;) {
                unsigned xs = (sx + rx) & 1023u, xd = (dx + rx) & 1023u;
                unsigned cols = width - rx;
                if (cols > 1024u - xs) cols = 1024u - xs;
                if (cols > 1024u - xd) cols = 1024u - xd;
                if (!copy_rectangle(c, xs, ys, xd, yd, cols, rows)) return 0;
                rx += cols;
            }
            ry += rows;
        }
    }
    c->accepted_gp0_words++;
    c->completed_copies++;
    discard_copy(c);
    return 1;
}

static int16_t offset11(uint32_t raw, unsigned shift) {
    uint32_t field = (raw >> shift) & 0x7ffu;
    return (int16_t)((field ^ 0x400u) - 0x400u);
}

static int clip_box(const MusashiGpuController *controller,
                    int *x0, int *y0, int *x1, int *y1) {
    int left = (int)(controller->drawing_area_start & 0x3ffu);
    int top = (int)((controller->drawing_area_start >> 10) & 0x1ffu);
    int right = (int)(controller->drawing_area_end & 0x3ffu);
    int bottom = (int)((controller->drawing_area_end >> 10) & 0x1ffu);
    if (right < left) { left = 0; right = 1023; }
    if (bottom < top) { top = 0; bottom = 511; }
    if (*x0 < left) *x0 = left;
    if (*y0 < top) *y0 = top;
    if (*x1 > right) *x1 = right;
    if (*y1 > bottom) *y1 = bottom;
    return *x0 <= *x1 && *y0 <= *y1;
}

static int plot_drawn(MusashiGpuController *controller, int x, int y,
                      uint16_t color) {
    if (x < 0 || y < 0 || x > 1023 || y > 511) return 1;
    if (!controller->backend.store_vram) return 0;
    if (!enter_callback(controller)) return 0;
    if (!finish_callback(controller,
            controller->backend.store_vram(controller->backend.userdata,
                                           (uint16_t)x, (uint16_t)y, color)))
        return 0;
    if (controller->drawn_pixels == UINT64_MAX) return 0;
    controller->drawn_pixels++;
    return controller->faulted ? 0 : 1;
}

static int fill_triangle(MusashiGpuController *controller,
                         int x0, int y0, int x1, int y1, int x2, int y2,
                         uint16_t color) {
    int minx = x0, miny = y0, maxx = x0, maxy = y0, x, y;
    long long area;
    if (x1 < minx) minx = x1;
    if (x2 < minx) minx = x2;
    if (y1 < miny) miny = y1;
    if (y2 < miny) miny = y2;
    if (x1 > maxx) maxx = x1;
    if (x2 > maxx) maxx = x2;
    if (y1 > maxy) maxy = y1;
    if (y2 > maxy) maxy = y2;
    if (!clip_box(controller, &minx, &miny, &maxx, &maxy)) return 1;
    area = (long long)(x1 - x0) * (y2 - y0) - (long long)(y1 - y0) * (x2 - x0);
    if (!area) return 1;
    for (y = miny; y <= maxy; ++y) {
        for (x = minx; x <= maxx; ++x) {
            long long w0 = (long long)(x1 - x) * (y2 - y) -
                           (long long)(y1 - y) * (x2 - x);
            long long w1 = (long long)(x2 - x) * (y0 - y) -
                           (long long)(y2 - y) * (x0 - x);
            long long w2 = (long long)(x0 - x) * (y1 - y) -
                           (long long)(y0 - y) * (x1 - x);
            if (area > 0) {
                if (w0 < 0 || w1 < 0 || w2 < 0) continue;
            } else if (w0 > 0 || w1 > 0 || w2 > 0) continue;
            if (!plot_drawn(controller, x, y, color)) return 0;
        }
    }
    return 1;
}

static int prim_commit(MusashiGpuController *controller) {
    uint32_t opcode = controller->prim_data[0] >> 24;
    uint16_t color = (uint16_t)(((controller->prim_data[0] >> 3) & 0x1fu) |
        ((controller->prim_data[0] >> 6) & 0x3e0u) |
        ((controller->prim_data[0] >> 9) & 0x7c00u));
    int ox = offset11(controller->drawing_offset, 0);
    int oy = offset11(controller->drawing_offset, 11);
    int x[4], y[4], i, count;
    {
        static unsigned trace_count;
        if (getenv("MUSASHI_GPU_TRACE_PRIMITIVES") && trace_count++ < 128u)
            fprintf(stderr,"GPU_PRIM op=%02x xy=%08x uv=%08x wh=%08x offset=%d,%d display=%u,%u size=%u,%u\n",
                opcode,controller->prim_data[1],controller->prim_data[2],controller->prim_data[3],
                ox,oy,controller->display.x,controller->display.y,
                controller->display.width,controller->display.height);
    }
    if (opcode == 0x64u) {
        unsigned tpage = controller->draw_mode & 0x1ffu;
        unsigned fmt = (tpage >> 7) & 3u;
        unsigned tx = (tpage & 15u) * 64u;
        unsigned ty = ((tpage >> 4) & 1u) * 256u;
        uint16_t clut = (uint16_t)(controller->prim_data[2] >> 16);
        unsigned clut_x = (unsigned)(clut & 0x3fu) * 16u;
        unsigned clut_y = (unsigned)(clut >> 6);
        int dest_x = (int)(int16_t)(controller->prim_data[1] & 0xffffu) + ox;
        int dest_y = (int)(int16_t)(controller->prim_data[1] >> 16) + oy;
        unsigned u0 = controller->prim_data[2] & 0xffu;
        unsigned v0 = (controller->prim_data[2] >> 8) & 0xffu;
        unsigned width = controller->prim_data[3] & 0xffffu;
        unsigned height = controller->prim_data[3] >> 16;
        unsigned px, py;
        if (!controller->backend.read_vram || !width || !height ||
            width > 256u || height > 256u) return 0;
        for (py = 0; py < height; ++py) {
            for (px = 0; px < width; ++px) {
                uint16_t packed = 0, out = 0;
                unsigned sx, sy, index;
                if (fmt == 2u) {
                    sx = tx + ((u0 + px) & 255u);
                    sy = ty + ((v0 + py) & 255u);
                    if (!controller->backend.read_vram(controller->backend.userdata,
                            (uint16_t)(sx & 1023u), (uint16_t)(sy & 511u), &out))
                        return 0;
                } else if (fmt == 1u) {
                    sx = tx + (((u0 + px) & 255u) >> 1);
                    sy = ty + ((v0 + py) & 255u);
                    if (!controller->backend.read_vram(controller->backend.userdata,
                            (uint16_t)(sx & 1023u), (uint16_t)(sy & 511u), &packed))
                        return 0;
                    index = ((u0 + px) & 1u) ? (packed >> 8) : (packed & 0xffu);
                    if (!controller->backend.read_vram(controller->backend.userdata,
                            (uint16_t)((clut_x + index) & 1023u),
                            (uint16_t)(clut_y & 511u), &out))
                        return 0;
                } else if (fmt == 0u) {
                    sx = tx + (((u0 + px) & 255u) >> 2);
                    sy = ty + ((v0 + py) & 255u);
                    if (!controller->backend.read_vram(controller->backend.userdata,
                            (uint16_t)(sx & 1023u), (uint16_t)(sy & 511u), &packed))
                        return 0;
                    index = (packed >> (((u0 + px) & 3u) * 4u)) & 15u;
                    if (!controller->backend.read_vram(controller->backend.userdata,
                            (uint16_t)((clut_x + index) & 1023u),
                            (uint16_t)(clut_y & 511u), &out))
                        return 0;
                } else return 0;
                if (!out)
                    continue;
                if (!plot_drawn(controller, dest_x + (int)px, dest_y + (int)py,
                                (uint16_t)(out & 0x7fffu)))
                    return 0;
            }
        }
        return 1;
    }
    if (opcode != 0x28u && opcode != 0x2au) return 0;
    count = opcode == 0x28u ? 3 : 4;
    for (i = 0; i < count; ++i) {
        x[i] = (int)(int16_t)(controller->prim_data[1u + (unsigned)i] & 0xffffu) + ox;
        y[i] = (int)(int16_t)(controller->prim_data[1u + (unsigned)i] >> 16) + oy;
    }
    if (!fill_triangle(controller, x[0], y[0], x[1], y[1], x[2], y[2], color))
        return 0;
    if (count == 4 &&
        !fill_triangle(controller, x[1], y[1], x[3], y[3], x[2], y[2], color))
        return 0;
    return 1;
}

static int prim_word(MusashiGpuController *controller, uint32_t word) {
    uint32_t opcode;
    if (controller->accepted_gp0_words == UINT64_MAX) return 0;
    if (controller->prim_needed) {
        if (controller->prim_got >= 12u) return 0;
        controller->prim_data[controller->prim_got++] = word;
        controller->accepted_gp0_words++;
        if (controller->prim_got == controller->prim_needed) {
            int accepted = prim_commit(controller);
            discard_prim(controller);
            return accepted && !controller->faulted;
        }
        return controller->faulted ? 0 : 1;
    }
    opcode = word >> 24;
    if (opcode == 0x28u) controller->prim_needed = 4;
    else if (opcode == 0x2au) controller->prim_needed = 5;
    else if (opcode == 0x64u) controller->prim_needed = 4;
    else return 0;
    controller->prim_data[0] = word;
    controller->prim_got = 1;
    controller->accepted_gp0_words++;
    return controller->faulted ? 0 : 1;
}

int musashi_gpu_controller_write32(MusashiGpuController *controller,
                                   uint32_t address, uint32_t value) {
    uint32_t opcode;
    uint32_t candidate;
    int ready;

    if (!controller) return 0;
    if (controller->executing) {
        controller->faulted = 1;
        return 0;
    }
    if (!backend_bound(controller) || controller->faulted) return 0;
    if (address == MUSASHI_GPU_GPUREAD) {
        opcode = value >> 24;
        /* An open packet owns every following GP0 word. Pixel payloads may
         * look like opcode 02/A0; they are still texels, not new commands. */
        if (controller->copy_words)
            return copy_word(controller, value);
        if (controller->fill_words)
            return fill_word(controller, value);
        if (controller->store_phase)
            return store_word(controller, value);
        if (controller->prim_needed)
            return prim_word(controller, value);
        if ((opcode & 0xe0u) == 0x80u)
            return copy_word(controller, value);
        if (opcode == 2u)
            return fill_word(controller, value);
        if (opcode == 0xa0u)
            return store_word(controller, value);
        if (opcode == 0x28u || opcode == 0x2au || opcode == 0x64u)
            return prim_word(controller, value);
        candidate = opcode == 0 || opcode == 1u || (opcode >= 0xe1u && opcode <= 0xe6u);
        if (candidate && controller->accepted_gp0_words == UINT64_MAX)
            return 0;
        if (opcode == 0 || opcode == 1u) {
            if (!backend_ready(controller, &ready) || !ready) return 0;
            controller->accepted_gp0_words++;
            return controller->faulted ? 0 : 1;
        }
        if (opcode == 0xe2u || opcode == 0xe3u || opcode == 0xe4u ||
            opcode == 0xe5u || opcode == 0xe6u) {
            uint32_t raw = value &
                (opcode == 0xe5u ? 0x003fffffu :
                 opcode == 0xe6u ? 0x00000003u : 0x000fffffu);
            if (!controller->backend.environment ||
                !backend_ready(controller, &ready) || !ready)
                return 0;
            if (!backend_environment(controller, value)) return 0;
            if (opcode == 0xe2u) controller->texture_window = raw;
            else if (opcode == 0xe3u) controller->drawing_area_start = raw;
            else if (opcode == 0xe4u) controller->drawing_area_end = raw;
            else if (opcode == 0xe5u) controller->drawing_offset = raw;
            else controller->mask_flags = raw;
            controller->accepted_gp0_words++;
            return controller->faulted ? 0 : 1;
        }
        if (opcode != 0xe1u) return 0;
        if (!backend_ready(controller, &ready) || !ready) return 0;
        if (!backend_draw_mode(controller, value)) return 0;
        controller->draw_mode = value & 0x3fffu;
        controller->accepted_gp0_words++;
        return controller->faulted ? 0 : 1;
    }
    if (address != MUSASHI_GPU_GPUSTAT) return 0;
    opcode = value >> 24;
    switch (opcode) {
    case 0x00u:
        if (!backend_reset(controller)) return 0;
        reset_state(controller);
        return controller->faulted ? 0 : 1;
    case 0x01u:
        if (!backend_clear_fifo(controller)) return 0;
        discard_fill(controller);
        discard_store(controller);
        discard_copy(controller);
        discard_prim(controller);
        return controller->faulted ? 0 : 1;
    case 0x02u:
        return 1;
    case 0x03u:
        ready = (value & 1u) == 0;
        if (!backend_display_enable(controller, ready)) return 0;
        controller->display_disabled = !ready;
        return controller->faulted ? 0 : 1;
    case 0x04u:
        controller->dma_direction = value & 3u;
        return 1;
    case 0x05u:
    case 0x06u:
    case 0x07u:
    case 0x08u:
        return display_write(controller, opcode, value);
    /* GP1 opcode 10 latches selected raw environment registers. */
    case 0x10u:
        switch (value & 7u) {
        case 2u: controller->read_latch = controller->texture_window; break;
        case 3u: controller->read_latch = controller->drawing_area_start; break;
        case 4u: controller->read_latch = controller->drawing_area_end; break;
        case 5u: controller->read_latch = controller->drawing_offset; break;
        default: break;
        }
        return 1;
    default:
        return 0;
    }
}
