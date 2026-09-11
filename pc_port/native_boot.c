/* Native startup owner, currently a diagnostic that stops at the first
 * unbound device/call. Entry data and recovered startup run in retail order.
 * No synthesized callback guards, IRQ masks, ready bits or menu state.
 * One source-owned CPU runs from the mapped CRT through supported calls.
 * Native initial registers are an explicit platform policy; reaching a
 * boundary here is not full BIOS cold-boot or title/menu parity. */
#include "musashi_boot_memory.h"
#include "musashi_callback_registration.h"
#include "musashi_irq_scheduler.h"
#include "musashi_dma_controller.h"
#include "musashi_cd_dma3.h"
#include "musashi_gpu_dma2.h"
#include "musashi_mdec_controller.h"
#include "musashi_dma_otc.h"
#include "musashi_scanline_timer.h"
#include "musashi_irq_policy.h"
#include "musashi_bios_kernel.h"
#include "musashi_bios_heap.h"
#include "musashi_bios_exception.h"
#include "musashi_gte_owner.h"
#include "musashi_bios_card.h"
#include "musashi_sio_controller.h"
#include "musashi_bios_backup_unit.h"
#include "musashi_bios_input.h"
#include "musashi_source_clock.h"
#include "musashi_timer2.h"
#include "musashi_device_epoch.h"
#include "musashi_gpu_psycross.h"
#include "musashi_disc_media.h"
#include "musashi_cd_controller.h"
#include "musashi_audio_sdl.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <openssl/sha.h>
#include <signal.h>

#include "musashi_x11_nograb.h"
#include "PsyX/PsyX_public.h"
#include "psx/libetc.h"

extern SDL_mutex *g_intrMutex;

static volatile sig_atomic_t host_stop_signal;
static void request_host_stop(int signal_number) {
    host_stop_signal = signal_number;
}

static int log_sample(uint64_t *counter, uint64_t first, uint64_t stride) {
    uint64_t n = *counter;
    if (*counter != UINT64_MAX) ++*counter;
    return n < first || (stride && (n % stride) == 0u);
}

typedef struct NativeBoot {
    MusashiBootMemory memory;
    uint8_t list_tail_before[448];
    int list_tail_captured;
    MusashiPsyCrossIrqRuntime irq;
    MusashiDmaController dma;
    MusashiMdecController mdec;
    MusashiScanlineTimer timer1;
    MusashiIrqPolicy irq_policy;
    MusashiBiosKernel bios;
    MusashiBiosExceptionImage exception_image;
    MusashiBiosImageDevice image_device;
    MusashiCpuTransferDevice cpu_transfer;
    MusashiGteOwner gte;
    unsigned host_service_depth;
    MusashiBiosHeap heap;
    MusashiHeapDevice heap_device;
    MusashiGpuIoDevice gpu_io;
    uint64_t heap_calls;
    MusashiBiosCard card;
    MusashiBiosCardStartDevice card_device;
    MusashiSioController sio;
    MusashiBiosBackupUnit backup_unit;
    const void *continuation;
    MusashiGpuController gpu;
    MusashiGpuPsyCross gpu_renderer;
    MusashiGpuBackend gpu_backend;
    MusashiGpuDevice gpu_device;
    int gpu_trace;
    int graphics_returned;
    MusashiCallbackRegistrationDevice registration;
    MusashiCallbackDevice callback;
    MusashiCdDevice cd;
    MusashiEventDevice event;
    MusashiInputDevice input;
    MusashiBiosInput bios_input;
    MusashiBiosInputDevice bios_input_device;
    MusashiBiosCallbackFrame bios_callback_frame;
    MusashiSourceClock source_clock;
    uint64_t cd_irq_production_limit;
    MusashiExecutionClock execution_clock;
    MusashiTimer2 timer2;
    MusashiDeviceEpoch epoch;
    uint64_t keyboard_polls;
    uint64_t gpu_reset_sequence;
    MusashiDiscMedia *media;
    MusashiCdOwned *cd_drive;
    MusashiCdDma3 *cd_dma;
    MusashiGpuDma2 *gpu_dma;
    MusashiDmaOtc *dma_otc;
    uint64_t gpu_dma_transfers_logged;
    MusashiCdRegisterDevice cd_registers;
    MusashiCdIrqServices cd_services;
    MusashiDmaCallbackRegistrationDevice dma_irq;
    int cd_event_busy;
    uint32_t common_delay;
    int common_delay_written;
    uint32_t spu_delay;
    uint32_t spu_dma_madr, spu_dma_bcr, spu_dma_chcr;
    uint64_t cd_irq_requests;
    uint64_t xa_sample_anchor;
    MusashiSpuCdAudio *spu;
    MusashiAudioSdl *audio;
    MusashiCdSpuDevice cd_spu;
    MusashiStartupPrefixDevice startup_devices;
    const char *exe_path;
    int opening_overlay_ready;
    int title_scene_reached;
    unsigned start_preview_frames;
    int start_preview_paused;
    int trace_cd_timing, cd_timing_active;
    uint64_t cd_host_start, cd_epoch_start;
} NativeBoot;

static int select_opening_overlay(NativeBoot *boot) {
    uint32_t first, second;
    if (boot->opening_overlay_ready) return 1;
    if (!musashi_boot_read32(&boot->memory,0x800ceec8u,&first) ||
        !musashi_boot_read32(&boot->memory,0x800ceeccu,&second) ||
        first != 0x3c02800cu || second != 0x944299e4u) return 0;
    musashi_boot_select_overlay_0004_words(1);
    boot->opening_overlay_ready = 1;
    fputs("native_boot: OVERLAY_SELECT member=4 source=GUEST_RAM bytes_replaced=0\n",stderr);
    return 1;
}

static int native_devices_shutdown(NativeBoot *boot) {
    if (boot->irq.scheduler.installed) return 0;
    if (boot->gpu_dma) {
        if (!musashi_gpu_dma2_close(boot->gpu_dma)) return 0;
        boot->gpu_dma = NULL;
    }
    if (boot->dma_otc) {
        if (!musashi_dma_otc_close(boot->dma_otc)) return 0;
        boot->dma_otc = NULL;
    }
    if (boot->heap.initialized && !musashi_bios_heap_destroy(&boot->heap)) return 0;
    if (boot->cd_dma) {
        if (!musashi_cd_dma3_close(boot->cd_dma)) return 0;
        boot->cd_dma = NULL;
    }
    if (boot->spu) {
        if (!musashi_spu_cd_audio_destroy(boot->spu)) return 0;
        boot->spu = NULL;
    }
    if (boot->audio) {
        if (!musashi_audio_sdl_destroy(boot->audio)) return 0;
        boot->audio = NULL;
    }
    if (boot->cd_drive) {
        if (!musashi_cd_owned_close(boot->cd_drive)) return 0;
        boot->cd_drive = NULL;
    }
    /* The source registration must already be gone. Never free a CPU while
     * its image/GTE consumers still borrow it, including partial init paths. */
    if (boot->gte.initialized) {
        int accepted=musashi_gte_owner_close(&boot->gte);
        fprintf(stderr,"native_boot: GTE_REMOVED accepted=%d\n",accepted);
        if (!accepted) return 0;
    }
    if (boot->exception_image.initialized) {
        int accepted=musashi_bios_exception_destroy(&boot->exception_image);
        fprintf(stderr,"native_boot: BIOS_IMAGE_REMOVED accepted=%d required=%d\n",accepted,boot->bios.exception_required);
        if (!accepted) return 0;
    }
    if (boot->irq.cpu_status) {
        int accepted=musashi_psycross_irq_runtime_close(&boot->irq);
        fprintf(stderr,"native_boot: CPU_RUNTIME_REMOVED accepted=%d\n",accepted);
        if (!accepted) return 0;
    }
    musashi_disc_media_close(boot->media);
    boot->media = NULL;
    return 1;
}

static int registration_read16(void *userdata, uint32_t address, uint16_t *value) {
    NativeBoot *boot = userdata;
    return musashi_irq_controller_read16(&boot->irq.controller, address, value);
}

static int registration_write16(void *userdata, uint32_t address, uint16_t value) {
    NativeBoot *boot = userdata;
    return musashi_irq_controller_write16(&boot->irq.controller, address, value);
}

static int change_clear_pad(void *userdata, int32_t value) {
    NativeBoot *boot = userdata;
    return musashi_irq_policy_change_pad(&boot->irq_policy, value);
}

static int exchange_clear_pad(void *userdata, int32_t value, int32_t *previous) {
    NativeBoot *boot = userdata;
    return musashi_irq_policy_exchange_pad(&boot->irq_policy, value, previous);
}

static int init_card(void *userdata, int32_t pad_started, int32_t *previous) {
    NativeBoot *boot = userdata;
    return musashi_bios_card_init_service(&boot->card, pad_started, previous);
}

static int execute_event(void *userdata, uint32_t callback) {
    NativeBoot *boot = userdata;
    return musashi_boot_execute_bios_event(&boot->memory, callback);
}

static int open_event(void *userdata, uint32_t class_word, uint32_t spec,
                      uint32_t mode, uint32_t callback, int32_t *handle) {
    NativeBoot *boot = userdata;
    int accepted = musashi_bios_events_open(&boot->bios.events, class_word, spec,
                                            mode, callback, handle);
    if (accepted)
        fprintf(stderr, "native_boot: EVENT_OPEN class=%08x spec=%08x mode=%08x callback=%08x handle=%08x\n",
                class_word, spec, mode, callback, (unsigned)*handle);
    return accepted;
}

static int enable_event(void *userdata, int32_t handle, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted = musashi_bios_events_enable(&boot->bios.events, handle, result);
    if (accepted)
        fprintf(stderr, "native_boot: EVENT_ENABLE handle=%08x result=%d\n", (unsigned)handle, *result);
    return accepted;
}

static int test_event(void *userdata, int32_t handle, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted = musashi_bios_events_test_sync_spu(&boot->bios.events, handle,
                                                     result);
    if (accepted)
        fprintf(stderr, "native_boot: EVENT_TEST handle=%08x result=%d\n", (unsigned)handle, *result);
    return accepted;
}

static int start_card(void *userdata, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted;
    if (boot->host_service_depth) return 0;
    boot->host_service_depth++;
    accepted=musashi_bios_card_start_service(&boot->card, result);
    boot->host_service_depth--;
    return accepted;
}

static int change_clear_timer(void *userdata, int32_t channel, int32_t value) {
    NativeBoot *boot = userdata;
    return musashi_irq_policy_change_timer(&boot->irq_policy, channel, value);
}

static int raise_vblank(void *userdata) {
    NativeBoot *boot = userdata;
    /* Hardware can become pending while guest interrupts are disabled. The
     * BIOS/custom ownership check belongs to delivery, not source latching. */
    return musashi_irq_controller_raise_vblank(&boot->irq.controller);
}

static int unavailable_bios_cd(void *userdata, uint16_t pending) {
    (void)userdata;
    fprintf(stderr, "native_boot: BIOS CD execution unavailable pending=%04x\n",
            (unsigned)pending);
    return 0;
}

static int before_irq_dispatch(void *userdata, uint16_t pending) {
    NativeBoot *boot = userdata;
    /* BIOS SIO can own and acknowledge VBlank while ChangeClearPad is 1.
     * Let its verifier/handler run, then check the remaining guest route. */
    if (!musashi_bios_kernel_dispatch_with_context(&boot->bios, pending,
            &boot->irq.scheduler.active_exception))
        return 0;
    pending = musashi_irq_controller_pending(&boot->irq.controller);
    return !(pending & 1u) || musashi_irq_policy_custom_vblank(&boot->irq_policy);
}

static int native_cpu_context(void *userdata, const void *continuation, MusashiCpuContext *out) {
    NativeBoot *boot = userdata;
    if (!boot || !out || !continuation || continuation != boot->continuation) return 0;
    if (boot->host_service_depth)
        return musashi_boot_cpu_context(continuation,MUSASHI_CPU_CONTEXT_HOST_BIOS_SERVICE,out);
    if (musashi_boot_cpu_context(continuation,MUSASHI_CPU_CONTEXT_SOURCE,out)) return 1;
    return musashi_boot_continuation_host_context(continuation,out);
}

static int native_sys(NativeBoot *boot, MusashiCpuExceptionKind kind, int host, int32_t *result) {
    MusashiCpuContext context;
    MusashiCpuExceptionToken token={0};
    int accepted;
    int32_t sys_result=0;
    if ((kind==MUSASHI_CPU_EXCEPTION_SYS1 && !result) || !boot->continuation || boot->irq.scheduler.delivering || boot->irq.scheduler.pumping ||
        !(host ? musashi_boot_cpu_context(boot->continuation,MUSASHI_CPU_CONTEXT_HOST_BIOS_SERVICE,&context) :
                 musashi_boot_cpu_context(boot->continuation,MUSASHI_CPU_CONTEXT_SOURCE,&context))) return 0;
    if (!musashi_cpu_status_begin(boot->irq.cpu_status,kind,&context,
            musashi_irq_controller_pending(&boot->irq.controller) ? 0x400u : 0u,&token)) return 0;
    accepted=musashi_bios_kernel_before_exception_with_context(&boot->bios,&token) &&
        musashi_cpu_status_apply_sys(boot->irq.cpu_status,&token,kind==MUSASHI_CPU_EXCEPTION_SYS1 ? &sys_result : NULL) &&
        musashi_cpu_status_finish(boot->irq.cpu_status,&token);
    if (!accepted) (void)musashi_cpu_status_fault(boot->irq.cpu_status,&token);
    else {
        MusashiCpuStatusSnapshot state;
        if (!musashi_cpu_status_snapshot(boot->irq.cpu_status,&state)) return 0;
        fprintf(stderr,"native_boot: CPU_SYS kind=%u provenance=%u sequence=%llu "
                "sr=%08x cause_valid=%d cause=%08x epc=%08x image_generation=%llu\n",
                (unsigned)kind,(unsigned)context.provenance,(unsigned long long)state.sequence,
                state.sr,state.cause_epc_valid,state.cause,state.epc,
                (unsigned long long)boot->exception_image.generation);
        if (kind==MUSASHI_CPU_EXCEPTION_SYS1) *result=sys_result;
    }
    return accepted;
}

static int remove_bios_cd(void *userdata, uint32_t table_address) {
    NativeBoot *boot = userdata;
    int32_t previous;
    (void)table_address;
    /* A0:72 contains a BIOS EnterCriticalSection call. This compiled BIOS
     * service has a real suspended caller but no invented physical EPC. */
    return native_sys(boot,MUSASHI_CPU_EXCEPTION_SYS1,1,&previous) &&
           musashi_bios_kernel_remove_cd(&boot->bios);
}
static int exit_critical(void *userdata) {
    return native_sys(userdata,MUSASHI_CPU_EXCEPTION_SYS2,0,NULL);
}
static int enter_critical_result(void *userdata, int32_t *result) {
    return result && native_sys(userdata,MUSASHI_CPU_EXCEPTION_SYS1,0,result);
}
static int card_exit_critical(void *userdata) {
    return native_sys(userdata,MUSASHI_CPU_EXCEPTION_SYS2,1,NULL);
}
/* Diagnostics derive eligibility from the same SR owner. -1 is an explicit
 * failed observation, never a replacement disabled/ready value. */
static int guest_irq_enabled(NativeBoot *boot) {
    int enabled=-1;
    if (!musashi_psycross_irq_scheduler_get_enabled(&boot->irq.scheduler,&enabled)) return -1;
    return enabled;
}

static int card_write_sio16(void *userdata, uint32_t address, uint16_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_sio_controller_write16(&boot->sio, address, value)) return 0;
    if (boot->gpu_trace)
        fprintf(stderr, "native_boot: CARD_TRACE address=%08x width=2 value=%08x\n",
                (unsigned)address, (unsigned)value);
    return 1;
}

static int card_read_sio16(void *userdata, uint32_t address, uint16_t *value) {
    NativeBoot *boot = userdata;
    return musashi_sio_controller_read16(&boot->sio, address, value);
}

static int card_read_sio8(void *userdata, uint32_t address, uint8_t *value) {
    NativeBoot *boot = userdata;
    return musashi_sio_controller_read8(&boot->sio, address, value);
}

static int card_write_sio8(void *userdata, uint32_t address, uint8_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_sio_controller_write8(&boot->sio, address, value)) return 0;
    if (boot->gpu_trace)
        fprintf(stderr, "native_boot: CARD_TRACE address=%08x width=1 value=%08x\n",
                (unsigned)address, (unsigned)value);
    return 1;
}

static int cards_disconnected(void *userdata) {
    NativeBoot *boot = userdata;
    return boot->sio.disconnected_cards == 1;
}

static int card_enter_critical(void *userdata) {
    int32_t previous;
    return native_sys(userdata,MUSASHI_CPU_EXCEPTION_SYS1,1,&previous);
}

static int card_read_pad(void *userdata, int32_t *value) {
    NativeBoot *boot = userdata;
    if (!value || !boot->irq_policy.pad_initialized) return 0;
    *value = boot->irq_policy.pad;
    return 1;
}

static int card_read_irq32(void *userdata, uint32_t address, uint32_t *value) {
    NativeBoot *boot = userdata;
    uint16_t low;
    if (!value || !musashi_irq_controller_read16(&boot->irq.controller, address, &low))
        return 0;
    *value = low;
    return 1;
}

static int card_write_irq32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_irq_controller_write16(&boot->irq.controller, address, (uint16_t)value))
        return 0;
    if (boot->gpu_trace)
        fprintf(stderr, "native_boot: CARD_TRACE address=%08x width=4 value=%08x\n",
                (unsigned)address, (unsigned)value);
    return 1;
}

static int input_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_irq_controller_write16(&boot->irq.controller, address, (uint16_t)value)) return 0;
    {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: INPUT_MMIO address=%08x width=4 value=%08x\n",
                    address, value);
    }
    return 1;
}

static int input_read16(void *userdata, uint32_t address, uint16_t *value) {
    NativeBoot *boot = userdata;
    /* SetIntrMask (800426FC) RMW uses halfword I_STAT/I_MASK through the same
     * input-device MMIO path as Timer2/SIO during BIOS input callbacks. */
    if (address == 0x1f801070u || address == 0x1f801074u)
        return musashi_irq_controller_read16(&boot->irq.controller, address, value);
    return musashi_sio_controller_read16(&boot->sio, address, value) ||
           musashi_timer2_read16(&boot->timer2, address, value);
}

static uint64_t epoch_owner(void *userdata) {
    (void)userdata;
    return (uint64_t)SDL_ThreadID();
}

static int init_heap(void *userdata, uint32_t base, uint32_t size) {
    NativeBoot *boot = userdata;
    uint32_t before=0, after=0;
    int before_valid=musashi_boot_read32(&boot->memory,base,&before);
    int accepted=musashi_bios_heap_init_heap(&boot->heap,base,size);
    int after_valid=musashi_boot_read32(&boot->memory,base,&after);
    ++boot->heap_calls;
    fprintf(stderr,"native_boot: HEAP_INIT accepted=%d base=%08x size=%08x "
            "before_valid=%d before=%08x after_valid=%d after=%08x "
            "cursor=%08x preferred=%08x end=%08x lazy=%d calls=%llu\n",
            accepted,base,size,before_valid,before,after_valid,after,
            boot->heap.cursor,boot->heap.preferred_size,boot->heap.end,
            boot->heap.lazy,(unsigned long long)boot->heap_calls);
    return accepted;
}

static int gpu_io_owned(NativeBoot *boot) {
    return boot && !boot->epoch.faulted && !boot->gpu.faulted && !boot->gpu.executing &&
        boot->gpu_backend.ready && boot->gpu_backend.ready(boot->gpu_backend.userdata)>=0;
}
static int gpu_dma_healthy(void *userdata) {
    return gpu_io_owned(userdata);
}
static void observe_gpu_dma(NativeBoot *boot, const char *stage) {
    MusashiGpuDma2State state;
    if (!boot->gpu_dma || !musashi_gpu_dma2_get_state(boot->gpu_dma,&state)) {
        fprintf(stderr,"native_boot: GPU_DMA2 stage=%s readable=0\n",stage);
        return;
    }
    {
        static uint64_t n;
        if (!log_sample(&n, 8u, 1024u) && !state.fault) return;
    }
    fprintf(stderr,"native_boot: GPU_DMA2 stage=%s readable=1 cycle=%llu due=%llu "
            "starts=%llu transfers=%llu fetched=%llu accepted=%llu start_madr=%08x "
            "madr=%08x bcr=%08x chcr=%08x nodes=%u headers=%u payload=%u "
            "accepted_in_transfer=%u fault=%u fault_node=%08x fault_word=%u "
            "store_phase=%u store_remaining=%u stored_pixels=%llu "
            "timing=REFERENCE_SYNCHRONOUS_SUBMIT_DEFERRED_COMPLETION hardware_parity=UNPROVEN\n",
            stage,(unsigned long long)state.cycle,(unsigned long long)state.due,
            (unsigned long long)state.starts,(unsigned long long)state.transfers,
            (unsigned long long)state.fetched_words,(unsigned long long)state.accepted_words,
            state.start_madr,state.madr,state.bcr,state.chcr,state.nodes,state.header_words,
            state.payload_words,state.accepted_in_transfer,(unsigned)state.fault,
            state.fault_node,state.fault_word,boot->gpu.store_phase,boot->gpu.store_remaining,
            (unsigned long long)boot->gpu.stored_pixels);
    if (state.fault) {
        uint32_t word=0, i, base=state.fault_node;
        fprintf(stderr,"native_boot: GPU_DMA2_FAULT_WORD address=%08x", state.fault_word);
        for (i=0;i<8u;++i) {
            musashi_boot_read32(&boot->memory, base+i*4u, &word);
            fprintf(stderr," %08x", word);
        }
        fputc('\n', stderr);
    }
}
static int gpu_io_read32(void *userdata, uint32_t address, uint32_t *value) {
    NativeBoot *boot=userdata;
    if (address==0x1f801820u || address==0x1f801824u ||
        (address>=0x1f801080u && address<=0x1f801098u))
        return musashi_mdec_read32(&boot->mdec,address,value);
    if (!gpu_io_owned(boot)) return 0;
    if (address==0x1f801810u || address==0x1f801814u)
        return musashi_gpu_controller_read32(&boot->gpu,address,value);
    if (address==0x1f8010a0u || address==0x1f8010a4u || address==0x1f8010a8u)
        return musashi_gpu_dma2_read32(boot->gpu_dma,address,value);
    if (address==0x1f8010e0u || address==0x1f8010e4u || address==0x1f8010e8u)
        return boot->dma_otc && musashi_dma_otc_read32(boot->dma_otc,address,value);
    return 0;
}
static int gpu_io_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot=userdata;
    if (address==0x1f801820u || address==0x1f801824u ||
        (address>=0x1f801080u && address<=0x1f801098u))
        return musashi_mdec_write32(&boot->mdec,address,value);
    int accepted;
    if (!gpu_io_owned(boot)) return 0;
    const char *capture = getenv("MUSASHI_NATIVE_GPU_RESET_CAPTURE");
    if (capture && address == 0x1f801814u && value == 0x03000001u) {
        /* Read-only capture at the following graphics-control submission.
         * This is evidence output, never an input to the running game. */
        FILE *file = fopen(capture, "wb");
        int written = file && fwrite(boot->memory.bytes, 1, MUSASHI_RAM_SIZE, file)
                               == MUSASHI_RAM_SIZE;
        if (file && fclose(file) != 0) written = 0;
        if (!written) {
            fputs("native_boot: GPU reset capture failed\n", stderr);
            return 0;
        }
    }
    if (address==0x1f801810u || address==0x1f801814u) {
        accepted=musashi_gpu_controller_write32(&boot->gpu,address,value);
        if (!accepted && address==0x1f801810u)
            fprintf(stderr,"native_boot: GP0_REFUSED value=%08x opcode=%02x "
                    "store_phase=%u fill_words=%u\n",
                    value,value>>24,boot->gpu.store_phase,boot->gpu.fill_words);
        if (accepted && address==0x1f801814u && (value>>24)==0)
            boot->gpu_reset_sequence=boot->epoch.last_sequence;
    } else if (address==0x1f8010a0u || address==0x1f8010a4u || address==0x1f8010a8u) {
        if (address==0x1f8010a8u && value==0x01000201u)
            fprintf(stderr,"native_boot: GPU_STORE_BEFORE_BLOCK phase=%u remaining=%u "
                    "pixels=%llu xy=%u,%u wh=%u,%u px=%u,%u\n",
                    boot->gpu.store_phase,boot->gpu.store_remaining,
                    (unsigned long long)boot->gpu.stored_pixels,
                    boot->gpu.store_x,boot->gpu.store_y,boot->gpu.store_w,boot->gpu.store_h,
                    boot->gpu.store_px,boot->gpu.store_py);
        accepted=musashi_gpu_dma2_write32(boot->gpu_dma,address,value);
        if (address==0x1f8010a8u && (value&0x01000000u)) observe_gpu_dma(boot,"START");
    } else if (address==0x1f8010e0u || address==0x1f8010e4u || address==0x1f8010e8u) {
        accepted=boot->dma_otc && musashi_dma_otc_write32(boot->dma_otc,address,value);
        if (accepted && address==0x1f8010e8u && (value&0x01000000u)) {
            MusashiDmaOtcState state;
            if (musashi_dma_otc_get_state(boot->dma_otc,&state))
                fprintf(stderr,"native_boot: DMA6_OTC chcr=%08x madr=%08x bcr=%08x "
                        "transfers=%llu words=%llu fault=%u\n",
                        state.chcr,state.madr,state.bcr,
                        (unsigned long long)state.transfers,
                        (unsigned long long)state.words,(unsigned)state.fault);
        }
    } else return 0;
    if (accepted && boot->gpu_trace)
        fprintf(stderr,"native_boot: GPU_TRACE address=%08x width=4 value=%08x\n",
                address,value);
    return accepted;
}

static int cd_hardware_healthy(void *userdata) {
    NativeBoot *boot = userdata;
    return boot->media && boot->gpu_renderer.initialized &&
           boot->gpu_renderer.owner_thread == (uint64_t)SDL_ThreadID() &&
           !boot->epoch.faulted;
}

static int raise_cd_irq(void *userdata) {
    NativeBoot *boot = userdata;
    if (!cd_hardware_healthy(boot) || boot->cd_irq_requests == UINT64_MAX) return 0;
    boot->irq.controller.status |= 0x0004u;
    ++boot->cd_irq_requests;
    return 1;
}

static int cd_data_transfer_idle(void *userdata, int *idle) {
    NativeBoot *boot = userdata;
    MusashiCdDma3State state;
    if (!idle || !boot->cd_dma ||
        !musashi_cd_dma3_get_state(boot->cd_dma, &state) ||
        state.fault != MUSASHI_CD_DMA3_OK) return 0;
    *idle = (state.chcr & 0x01000000u) == 0;
    return 1;
}

static int deliver_cd_event(void *userdata, uint32_t class_word, uint32_t spec) {
    NativeBoot *boot = userdata;
    MusashiPsyCrossIrqScheduler *scheduler = &boot->irq.scheduler;
    int accepted;
    if (scheduler->owner_thread != (uint64_t)SDL_ThreadID() ||
        !scheduler->installed || !scheduler->delivering || scheduler->faulted ||
        !scheduler->active_continuation || scheduler->return_consumed ||
        !boot->irq.cd_frame.busy || boot->irq.cd_frame.faulted ||
        boot->cd_event_busy || boot->epoch.faulted ||
        class_word != 0xf0000003u || (spec != 0x20u && spec != 0x40u)) return 0;
    boot->cd_event_busy = 1;
    /* The live startup table contains card and SPU records, not CD callback
     * records. Polling matches use the real table transition. A new matching
     * guest callback requires a clocked executor and is refused here. */
    accepted = musashi_bios_events_deliver(&boot->bios.events, class_word, spec,
                                          NULL, NULL);
    boot->cd_event_busy = 0;
    fprintf(stderr, "native_boot: CD_EVENT class=%08x spec=%08x accepted=%d cycle=%llu\n",
            class_word, spec, accepted, (unsigned long long)boot->epoch.cycle);
    return accepted;
}

static int submit_xa_pcm(void *userdata,uint64_t cycle,uint64_t first_frame,
                          const int16_t *pcm,size_t frames) {
    NativeBoot *boot=userdata;MusashiSpuCdAudioSnapshot state;
    if (!boot->spu || !musashi_spu_cd_audio_snapshot(boot->spu,&state))return 0;
    if (!first_frame) {
        boot->xa_sample_anchor=cycle/768u+(cycle%768u!=0);
        if (boot->xa_sample_anchor<state.sample_index)boot->xa_sample_anchor=state.sample_index;
    }
    if (first_frame>UINT64_MAX-boot->xa_sample_anchor)return 0;
    if (boot->xa_sample_anchor+first_frame<state.sample_index) {
        /* A native transport underrun leaves silence already rendered by
         * the SPU. Queue every arriving PCM frame at the next available
         * sample and retain that new contiguous anchor; never discard PCM. */
        uint64_t gap=state.sample_index-(boot->xa_sample_anchor+first_frame);
        fprintf(stderr,"native_boot: XA_UNDERRUN silence_frames=%llu first=%llu\n",
                (unsigned long long)gap,(unsigned long long)first_frame);
        boot->xa_sample_anchor+=gap;
    }
    if (!musashi_spu_cd_audio_submit_cd_pcm(boot->spu,boot->xa_sample_anchor+first_frame,pcm,frames)) {
        fprintf(stderr,"native_boot: XA_PCM_REFUSED frame=%llu sample=%llu current=%llu\n",
                (unsigned long long)first_frame,(unsigned long long)(boot->xa_sample_anchor+first_frame),
                (unsigned long long)state.sample_index);return 0;
    }
    fprintf(stderr,"native_boot: XA_PCM frames=%zu first=%llu cycle=%llu\n",frames,
            (unsigned long long)first_frame,(unsigned long long)cycle);return 1;
}

static int cd_write8(void *userdata, uint32_t address, uint8_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_cd_owned_write8(boot->cd_drive, address, value)) return 0;
    fprintf(stderr, "native_boot: CD_WRITE address=%08x value=%02x cycle=%llu\n",
            address, value, (unsigned long long)boot->epoch.cycle);
    if (boot->trace_cd_timing && address == 0x1f801803u) {
        MusashiCdOwnedState s;
        if (musashi_cd_owned_get_state(boot->cd_drive,&s))
            fprintf(stderr,"native_boot: CD_TRACE bank=%u if=%u announced=%u claimed=%u incoming=%u incoming_lba=%u requested=%u fifo_lba=%u cursor=%u\n",
                s.index,s.interrupt,s.announced_lba,s.announced_claimed,
                s.incoming_valid,s.incoming_lba,s.data_requested,s.fifo_lba,s.fifo_cursor);
    }
    return 1;
}

static int cd_read8(void *userdata, uint32_t address, uint8_t *value) {
    NativeBoot *boot = userdata;
    if (!musashi_cd_owned_read8(boot->cd_drive, address, value)) return 0;
    if (address == 0x1f801801u)
        fprintf(stderr, "native_boot: CD_RESPONSE address=%08x value=%02x cycle=%llu\n",
                address, *value, (unsigned long long)boot->epoch.cycle);
    return 1;
}

static int cd_dma_healthy(void *userdata) {
    NativeBoot *boot = userdata;
    MusashiCdOwnedState state;
    return cd_hardware_healthy(boot) &&
        musashi_cd_owned_get_state(boot->cd_drive, &state) && state.fault == MUSASHI_CD_OWNED_OK;
}

static int cd_dma_request(void *userdata, int *asserted) {
    MusashiCdOwnedState state;
    if (!asserted || !musashi_cd_owned_get_state(((NativeBoot *)userdata)->cd_drive,&state) ||
        state.fault) return 0;
    *asserted = state.data_requested != 0;
    return 1;
}

static int cd_dma_available(void *userdata, size_t *available) {
    NativeBoot *boot = userdata;
    MusashiCdOwnedState state;
    if (!available || !musashi_cd_owned_get_state(boot->cd_drive, &state) ||
        state.fault || state.fifo_cursor > state.fifo_size) return 0;
    *available = state.data_requested && state.fifo_valid ? state.fifo_size-state.fifo_cursor : 0;
    return 1;
}

static int cd_dma_read_data(void *userdata, uint8_t *destination, size_t bytes) {
    return musashi_cd_owned_read_data(((NativeBoot *)userdata)->cd_drive, destination, bytes);
}

static int cd_read32(void *userdata, uint32_t address, uint32_t *value) {
    NativeBoot *boot = userdata;
    if (address == 0x1f8010f0u)
        return cd_dma_healthy(boot) && musashi_dma_controller_read32(&boot->dma, address, value);
    if (address == 0x1f801014u) {
        if (!value) return 0;
        *value = boot->spu_delay;
        return 1;
    }
    if (address == 0x1f8010c0u) {
        if (!value) return 0;
        *value = boot->spu_dma_madr;
        return 1;
    }
    if (address == 0x1f8010c4u) {
        if (!value) return 0;
        *value = boot->spu_dma_bcr;
        return 1;
    }
    if (address == 0x1f8010c8u) {
        if (!value) return 0;
        *value = boot->spu_dma_chcr;
        return 1;
    }
    return musashi_cd_dma3_read32(boot->cd_dma, address, value);
}

static int cd_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    if (!cd_dma_healthy(boot)) return 0;
    if (address == 0x1f8010f0u) {
        if (!musashi_dma_controller_write32(&boot->dma, address, value)) return 0;
    } else if (address == 0x1f801020u) {
        boot->common_delay=value;
        boot->common_delay_written=1;
    } else if (address == 0x1f801014u) {
        boot->spu_delay=value;
    } else if (address == 0x1f8010c0u) {
        boot->spu_dma_madr=value;
    } else if (address == 0x1f8010c4u) {
        boot->spu_dma_bcr=value;
    } else if (address == 0x1f8010c8u) {
        boot->spu_dma_chcr=value;
    } else if (!musashi_cd_dma3_write32(boot->cd_dma,address,value)) {
        MusashiCdDma3State state;
        if (musashi_cd_dma3_get_state(boot->cd_dma,&state))
            fprintf(stderr,"native_boot: CD_WORD_REFUSED address=%08x value=%08x "
                    "cycle=%llu dma_cycle=%llu due=%llu chcr=%08x bcr=%08x "
                    "madr=%08x delay=%08x waiting=%u fault=%u\n",
                    address,value,(unsigned long long)boot->epoch.cycle,
                    (unsigned long long)state.cycle,(unsigned long long)state.due,
                    state.chcr,state.bcr,state.madr,state.cdrom_delay,
                    state.waiting_for_request,(unsigned)state.fault);
        return 0;
    }
    fprintf(stderr,"native_boot: CD_WORD_WRITE address=%08x value=%08x cycle=%llu\n",
            address,value,(unsigned long long)boot->epoch.cycle);
    return 1;
}

static int spu_read16(void *userdata, uint32_t address, uint16_t *value) {
    NativeBoot *boot = userdata;
    if (!musashi_spu_cd_audio_read16(boot->spu, address, value)) return 0;
    fprintf(stderr, "native_boot: SPU_READ address=%08x value=%04x cycle=%llu\n",
            address, (unsigned)*value, (unsigned long long)boot->epoch.cycle);
    return 1;
}

static int spu_write16(void *userdata, uint32_t address, uint16_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_spu_cd_audio_write16(boot->spu, address, value)) return 0;
    fprintf(stderr, "native_boot: SPU_WRITE address=%08x value=%04x cycle=%llu\n",
            address, (unsigned)value, (unsigned long long)boot->epoch.cycle);
    return 1;
}

static int sample_keyboard_pad(void *userdata, uint16_t *buttons) {
    NativeBoot *boot = userdata;
    const Uint8 *keys;
    int count;
    unsigned i;
    uint16_t sampled = 0xffffu;
    /* Native keyboard policy follows the pinned PsyCross default mapping.
     * Digital L3/R3 remain high. Sample real key state once at PAD byte01;
     * neither a missing SDL context nor a failed provider means neutral input. */
    static const struct { SDL_Scancode key; unsigned bit; } mapping[] = {
        {SDL_SCANCODE_SPACE,0}, {SDL_SCANCODE_RETURN,3},
        {SDL_SCANCODE_UP,4}, {SDL_SCANCODE_RIGHT,5},
        {SDL_SCANCODE_DOWN,6}, {SDL_SCANCODE_LEFT,7},
        {SDL_SCANCODE_LCTRL,8}, {SDL_SCANCODE_RCTRL,9},
        {SDL_SCANCODE_LSHIFT,10}, {SDL_SCANCODE_RSHIFT,11},
        {SDL_SCANCODE_Z,12}, {SDL_SCANCODE_V,13},
        {SDL_SCANCODE_C,14}, {SDL_SCANCODE_X,15}
    };
    if (!buttons) return 0;
    /* SIO write8 treats a failed sampler as a hardware fault and latches
     * sio->faulted permanently. A missing GL context is not a disconnected
     * pad: return idle (all bits high) so TAP can complete. */
    *buttons = 0xffffu;
    /* TAP samples from the BIOS vblank callback. SDL key state does not
     * require a current GL context; refusing here leaves analog idle. */
    if (!SDL_WasInit(SDL_INIT_VIDEO) || boot->keyboard_polls == UINT64_MAX)
        return 1;
    /* Do not PumpEvents here: on Xwayland that re-asserts XSetInputFocus
     * from TAP/SIO and steals the desktop keyboard. HOLD_* env is enough. */
    keys = SDL_GetKeyboardState(&count);
    if (!keys) return 1;
    for (i = 0; i < sizeof(mapping) / sizeof(mapping[0]); ++i) {
        if ((int)mapping[i].key >= count) return 0;
        if (keys[mapping[i].key]) sampled &= (uint16_t)~(1u << mapping[i].bit);
    }
    if ((SDL_GetModState() & KMOD_RSHIFT) != 0)
        sampled &= (uint16_t)~(1u << 11);
    /* Host hold: xdotool/Xwayland often never reaches SDL_GetKeyboardState.
     * 80018C64 stores inverted buttons byte-swapped, so Start (bit 3) lands
     * as 0x0800 at +0x2A; analog 80018CE8 writes the EDGE into +0x3A (78DD2).
     * Holding Start from cold boot or overlay-load spends that edge in
     * table[0]/[1] before 800CEF94 polls 80014CAC(0, 0x800). */
    {
        const char *hold = getenv("MUSASHI_HOLD_R1");
        if (hold && hold[0] && hold[0] != '0')
            sampled &= (uint16_t)~(1u << 11);
        /* Press Start while overlay 0007 is live, never after the title
         * scene: Cross/Start on the title would load a new game.
         * Injecting only at A3B4==2 races TAP: 800118AC increments to 2
         * then 800CF3B0 samples the previous frame's 78DD2. Holding Start
         * for the whole 0007 path lets 800CF3B0 set A3B6. Do not fprintf
         * here: TAP during that log clears 78DD2. */
        const char *auto_start = getenv("MUSASHI_BOOT_AUTO_START");
        if (auto_start && auto_start[0] == '1' &&
            boot->opening_overlay_ready && !boot->title_scene_reached)
            sampled &= (uint16_t)~(1u << 3);
    }
    ++boot->keyboard_polls;
    *buttons = sampled;
    return 1;
}

static int raise_sio_irq(void *userdata, uint16_t mask) {
    NativeBoot *boot = userdata;
    if (mask != 0x80u) return 0;
    /* ACK IRQ is a CPU status latch, not a GL operation. Refusing it off the
     * window thread faults SIO permanently and leaves 29B4 at FFFFFFFF. */
    boot->irq.controller.status |= mask;
    return 1;
}

static int input_write8(void *userdata, uint32_t address, uint8_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_sio_controller_write8(&boot->sio, address, value)) return 0;
    {
        static uint64_t n;
        if (log_sample(&n, 16u, 4096u))
            fprintf(stderr, "native_boot: INPUT_DATA address=%08x value=%02x cycle=%llu\n",
                    address, (unsigned)value, (unsigned long long)boot->sio.cycle);
    }
    return 1;
}

static int epoch_collect(void *userdata, MusashiIrqSourceBatch *batch) {
    NativeBoot *boot = userdata;
    if (boot->irq.scheduler.installed)
        return musashi_psycross_irq_scheduler_collect_source(&boot->irq.scheduler, batch);
    /* Before source installation there are no owned callbacks to collect.
     * Never substitute an empty queue after a source has been removed. */
    if (boot->irq.scheduler.source_sequence || boot->irq.scheduler.faulted) return 0;
    memset(batch, 0, sizeof(*batch));
    batch->frequency = SDL_GetPerformanceFrequency();
    batch->cut_tick = SDL_GetPerformanceCounter();
    return batch->frequency != 0;
}

static int epoch_wait(void *userdata, uint64_t target_tick) {
    NativeBoot *boot = userdata;
    uint64_t previous = SDL_GetPerformanceCounter();
    Uint32 started = SDL_GetTicks();
    for (;;) {
        uint64_t now = SDL_GetPerformanceCounter();
        if (now < previous) return 0;
        if (now >= target_tick) return 1;
        if ((Uint32)(SDL_GetTicks() - started) >= 1000u) return 0;
        if (target_tick - now > boot->epoch.frequency / 500u) SDL_Delay(1);
        else SDL_Delay(0);
        previous = now;
    }
}

static int advance_cd_devices(NativeBoot *boot, uint64_t cycle) {
    MusashiCdDma3State dma;
    MusashiCdOwnedState cd;
    uint64_t cd_cycle = cycle;
    static uint64_t bounded_cuts;
    if (!boot->cd_drive) return 1;
    if (!boot->cd_dma || !musashi_cd_dma3_get_state(boot->cd_dma,&dma)) return 0;
    if (!musashi_cd_owned_get_state(boot->cd_drive, &cd)) return 0;
    /* A chopped transfer must finish using its latched sector before the
     * next streaming notification can make the source release that FIFO.
     * Host catch-up must not compress a sector period across active DMA. */
    if (cd.command == 0x1bu && (dma.chcr & 0x01000000u)) {
        if (!musashi_cd_dma3_advance(boot->cd_dma,cycle) ||
            !musashi_cd_dma3_get_state(boot->cd_dma,&dma)) return 0;
        if ((dma.chcr & 0x01000000u) && !dma.waiting_for_request) return 1;
    }
    if (cd.command == 0x1bu && !cd.phase && !cd.incoming_valid && boot->spu) {
        MusashiSpuCdAudioSnapshot audio;
        if (!musashi_spu_cd_audio_snapshot(boot->spu,&audio)) return 0;
        /* Bound native producer catch-up by real PCM queue capacity. The
         * SPU continues consuming on the epoch; no sector/audio is dropped. */
        if (audio.pending_frames > MUSASHI_SPU_CD_AUDIO_QUEUE_LIMIT-2352u)
            return musashi_cd_dma3_advance(boot->cd_dma,cycle);
    }
    /* A streaming IRQ's host execution/logging cost is not guest CD time.
     * Use the current source instruction's production limit within that IRQ;
     * DMA transport keeps its existing absolute owner clock. */
    if (boot->irq.cd_frame.busy && cd.command == 0x1bu &&
        boot->cd_irq_production_limit && cd_cycle > boot->cd_irq_production_limit)
        cd_cycle = boot->cd_irq_production_limit;
    if (cd.incoming_valid) {
        uint64_t target = cd.cycle;
        if (cd.phase && cd.due > cd.cycle && cd.due <= cd_cycle)
            target = cd.due;
        /* A decoder can claim the previous announcement while another
         * sector waits in incoming. Service that publication deadline even
         * without a new command; advance_without_fetch retains backpressure. */
        if (!cd.interrupt && !cd.response_count &&
            (!cd.announced_valid || cd.announced_claimed || cd.command == 0x1bu) &&
            cd.sector_publish_due > cd.cycle && cd.sector_publish_due <= cd_cycle &&
            (target == cd.cycle || cd.sector_publish_due < target))
            target = cd.sector_publish_due;
        if (target != cd.cycle) {
            ++bounded_cuts;
            if (bounded_cuts <= 8u || (bounded_cuts & 255u) == 0u)
                fprintf(stderr, "native_boot: CD_COMMAND_WHILE_STALLED count=%llu "
                        "requested=%llu target=%llu command=%02x due=%llu\n",
                        (unsigned long long)bounded_cuts,
                        (unsigned long long)cycle, (unsigned long long)target,
                        cd.command, (unsigned long long)cd.due);
        }
        if ((dma.chcr & 0x01000000u) && dma.due <= target) {
            if (!musashi_cd_owned_advance_without_fetch(boot->cd_drive, dma.due) ||
                !musashi_cd_dma3_advance(boot->cd_dma, dma.due)) return 0;
        }
        if (target > cd.cycle &&
            !musashi_cd_owned_advance_without_fetch(boot->cd_drive, target))
            return 0;
        return musashi_cd_dma3_advance(boot->cd_dma, cycle);
    }
    /* Deliver a streaming sector at its own deadline, not one cycle
     * before the following sector. That leaves its actual transfer period
     * available to the guest callback even after a large host catch-up. */
    if (cd.command == 0x1bu && cd.sector_due >= cd.cycle &&
        cd.sector_due && cd_cycle > cd.sector_due)
        cd_cycle = cd.sector_due;
    cd_cycle = musashi_cd_owned_bounded_cycle(&cd, cd_cycle);
    if (cd_cycle != cycle) {
        ++bounded_cuts;
        if (bounded_cuts <= 8u || (bounded_cuts & 255u) == 0u)
            fprintf(stderr, "native_boot: CD_BOUNDED count=%llu requested=%llu "
                    "bounded=%llu incoming=%u claimed=%u sector_due=%llu\n",
                    (unsigned long long)bounded_cuts,
                    (unsigned long long)cycle, (unsigned long long)cd_cycle,
                    cd.incoming_valid, cd.announced_claimed,
                    (unsigned long long)cd.sector_due);
    }
    /* A cut can cross a DMA completion and a later CD production deadline.
     * Consume its FIFO at the earlier DMA deadline before advancing the drive
     * to the end of the cut. Device callbacks cannot start another transfer. */
    if ((dma.chcr & 0x01000000u) && dma.due <= cd_cycle) {
        if (!musashi_cd_owned_advance(boot->cd_drive,dma.due) ||
            !musashi_cd_dma3_advance(boot->cd_dma,dma.due)) return 0;
    }
    return musashi_cd_owned_advance(boot->cd_drive,cd_cycle) &&
        musashi_cd_dma3_advance(boot->cd_dma,cycle);
}

static int epoch_advance_devices(void *userdata, uint64_t cycle) {
    NativeBoot *boot = userdata;
    MusashiGpuDma2State gpu;
    /* Deterministic native CD-before-GPU order; physical bus priority is not
     * modeled. Device reads never supply time or dispatch guest callbacks. */
    int accepted=musashi_timer2_advance(&boot->timer2, cycle) &&
           musashi_sio_controller_advance(&boot->sio, cycle) &&
           musashi_scanline_timer_advance(&boot->timer1, cycle) &&
           advance_cd_devices(boot, cycle) &&
           musashi_mdec_advance(&boot->mdec, cycle) &&
           (!boot->gpu_dma || musashi_gpu_dma2_advance(boot->gpu_dma,cycle)) &&
           (!boot->spu || musashi_spu_cd_audio_advance(boot->spu, cycle));
    if (boot->gpu_dma && musashi_gpu_dma2_get_state(boot->gpu_dma,&gpu) &&
        gpu.transfers != boot->gpu_dma_transfers_logged) {
        observe_gpu_dma(boot,"COMPLETE");
        boot->gpu_dma_transfers_logged=gpu.transfers;
    }
    return accepted;
}

static void host_window_inspect(SDL_Window *window);

static int epoch_video_edge(void *userdata, uint64_t sequence, uint64_t cycle) {
    NativeBoot *boot = userdata;
    (void)sequence;
    if (!musashi_scanline_timer_vblank_at(&boot->timer1, cycle) ||
        !musashi_gpu_controller_vblank(&boot->gpu) || !raise_vblank(boot))
        return 0;
    /* Host scanout only. Failure here must not fault the epoch; present
     * already refuses when the GPU backend is mid-command. */
    if (boot->gpu_renderer.display_enabled)
        (void)musashi_gpu_psycross_present(&boot->gpu_renderer);
    return 1;
}

static int advance_source_clock(void *userdata, uint32_t cycles) {
    NativeBoot *boot = userdata;
    uint64_t cycle;
    if (host_stop_signal) return 0;
    if (boot->trace_cd_timing) {
        if (boot->irq.cd_frame.busy && !boot->cd_timing_active) {
            boot->cd_timing_active = 1;
            boot->cd_host_start = SDL_GetPerformanceCounter();
            boot->cd_epoch_start = boot->epoch.cycle;
        } else if (!boot->irq.cd_frame.busy && boot->cd_timing_active) {
            boot->cd_timing_active = 0;
            if (boot->irq.cd_frame.instructions > 16384u)
                fprintf(stderr,"native_boot: CD_TIMING instructions=%u host_us=%llu epoch_cycles=%llu\n",
                    boot->irq.cd_frame.instructions,
                    (unsigned long long)((SDL_GetPerformanceCounter()-boot->cd_host_start)*1000000u/SDL_GetPerformanceFrequency()),
                    (unsigned long long)(boot->epoch.cycle-boot->cd_epoch_start));
        }
    }
    if (boot->bios_callback_frame.busy) {
        /* TAP busy-waits RC2 for 400 ticks (~3200 CPU cycles). Syncing that
         * wait to wall time expires the window during host fprintf. Tick
         * SIO/RC2 by instruction cost only, matching input_digital_irq_probe.
         * Never reverse SIO time if the shared epoch already advanced it. */
        uint64_t base = boot->timer2.last_cycles;
        if (boot->sio.cycle > base) base = boot->sio.cycle;
        if (base > UINT64_MAX - cycles) return 0;
        cycle = base + cycles;
        return musashi_timer2_advance(&boot->timer2, cycle) &&
               musashi_sio_controller_advance(&boot->sio, cycle);
    }
    boot->cd_irq_production_limit = 0;
    if (boot->irq.cd_frame.busy && boot->cd_drive) {
        MusashiCdOwnedState cd;
        if (!musashi_cd_owned_get_state(boot->cd_drive,&cd) || cd.cycle > UINT64_MAX-cycles)
            return 0;
        boot->cd_irq_production_limit = cd.cycle + cycles;
    }
    if (!musashi_source_clock_advance(&boot->source_clock, cycles)) return 0;
    if (!musashi_device_epoch_advance_cost(&boot->epoch, cycles)) {
        boot->source_clock.faulted = 1;
        return 0;
    }
    return 1;
}

static int input_write16(void *userdata, uint32_t address, uint16_t value) {
    NativeBoot *boot = userdata;
    if (address == 0x1f801070u || address == 0x1f801074u) {
        if (!musashi_irq_controller_write16(&boot->irq.controller, address, value)) return 0;
        {
            static uint64_t n;
            if (log_sample(&n, 8u, 4096u))
                fprintf(stderr, "native_boot: INPUT_MMIO address=%08x width=2 value=%08x\n",
                        address, (unsigned)value);
        }
        return 1;
    }
    if (!musashi_sio_controller_write16(&boot->sio, address, value)) return 0;
    {
        static uint64_t n;
        if (log_sample(&n, 16u, 4096u))
            fprintf(stderr, "native_boot: INPUT_SERIAL_MMIO address=%08x width=2 value=%08x\n",
                    address, (unsigned)value);
    }
    return 1;
}

static int input_dequeue(void *userdata, int32_t priority, uint32_t descriptor, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted = musashi_bios_input_dequeue(&boot->bios_input, priority, descriptor, result);
    if (accepted) fprintf(stderr, "native_boot: INPUT_C003 priority=%d descriptor=%08x result=%08x\n",
                          priority, descriptor, (unsigned)*result);
    return accepted;
}

static int input_enqueue(void *userdata, int32_t priority, uint32_t descriptor, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted = musashi_bios_input_enqueue(&boot->bios_input, priority, descriptor, result);
    if (accepted) fprintf(stderr, "native_boot: INPUT_C002 priority=%d descriptor=%08x result=%08x\n",
                          priority, descriptor, (unsigned)*result);
    return accepted;
}

static int input_change_timer(void *userdata, int32_t channel, int32_t value, int32_t *result) {
    NativeBoot *boot = userdata;
    int accepted = musashi_irq_policy_exchange_timer(&boot->irq_policy, channel, value, result);
    if (accepted) fprintf(stderr, "native_boot: INPUT_C00A channel=%d value=%08x result=%08x\n",
                          channel, (unsigned)value, (unsigned)*result);
    return accepted;
}

static int input_execute(void *userdata, uint32_t target, int32_t argument, int32_t *result) {
    NativeBoot *boot = userdata;
    MusashiResetGraphPrefixStop stop = {0};
    const void *continuation = boot->continuation;
    int accepted = musashi_boot_execute_input_bios_callback(&boot->memory, &boot->input,
        &boot->bios_callback_frame, target, argument, result, &stop);
    if (boot->timer2.last_cycles > boot->epoch.cycle) {
        boot->timer2.last_cycles = boot->epoch.cycle;
        boot->sio.cycle = boot->epoch.cycle;
    }
    if (boot->continuation != continuation) return 0;
    if (accepted) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: INPUT_CALLBACK target=%08x argument=%08x result=%08x\n",
                    target, (unsigned)argument, (unsigned)*result);
        return 1;
    }
    if (host_stop_signal) {
        /* Host SIGTERM/SIGINT aborts mid-callback clock advance. Soft-complete
         * so BIOS input/IRQ owners stay healthy for teardown and the next run. */
        boot->bios_callback_frame.faulted = 0;
        boot->bios_callback_frame.busy = 0;
        boot->bios_input.faulted = 0;
        *result = 0;
        fprintf(stderr, "native_boot: INPUT_CALLBACK_ABORTED entry=%08x pc=%08x target=%08x\n",
                target, stop.call_address, stop.target_address);
        return 1;
    }
    fprintf(stderr, "native_boot: INPUT_CALLBACK_REFUSED entry=%08x pc=%08x target=%08x\n",
            target, stop.call_address, stop.target_address);
    return 0;
}

static void observe_input_state(NativeBoot *boot, uint32_t pc) {
    const uint32_t addresses[] = {0x80078988u,0x8007898cu,0x80078990u,0x80078994u,
        0x80072994u,0x800729acu,0x800729b0u,0x80072990u,0x80072984u,
        0x80078998u,0x8007899cu,0x800729c4u,0x800729a0u,0x8007299cu};
    unsigned i;
    for (i = 0; i < sizeof(addresses)/sizeof(addresses[0]); ++i) {
        uint32_t value;
        if (!musashi_boot_read32(&boot->memory, addresses[i], &value)) return;
        fprintf(stderr, "native_boot: INPUT_RAM at=%08x address=%08x value=%08x\n", pc, addresses[i], value);
    }
    fprintf(stderr, "native_boot: INPUT_OWNER at=%08x installed=%d faulted=%d frame_busy=%d frame_faulted=%d timer3=%d\n",
            pc, boot->bios_input.node.owner == &boot->bios, boot->bios_input.faulted,
            boot->bios_callback_frame.busy, boot->bios_callback_frame.faulted, boot->irq_policy.timers[3]);
}

static int cpu_read_status(void *userdata,const MusashiCpuContext *context,uint32_t *value) {
    NativeBoot *boot=userdata;
    if (!context || context->identity!=boot->continuation ||
        context->provenance!=MUSASHI_CPU_CONTEXT_SOURCE || !context->instruction_valid ||
        (context->instruction & 0xffe0ffffu)!=0x40006000u) return 0;
    int accepted=musashi_cpu_status_read(boot->irq.cpu_status,value);
    if (accepted) fprintf(stderr,"native_boot: CPU_STATUS_READ pc=%08x value=%08x\n",context->pc,*value);
    return accepted;
}
static int cpu_write_status(void *userdata,const MusashiCpuContext *context,uint32_t value) {
    NativeBoot *boot=userdata;
    int accepted=context && context->identity==boot->continuation &&
        musashi_cpu_status_write_source(boot->irq.cpu_status,context,value);
    if (accepted) fprintf(stderr,"native_boot: CPU_STATUS_WRITE pc=%08x value=%08x\n",context->pc,value);
    return accepted;
}
static int cpu_write_control(void *userdata,const MusashiCpuContext *context,uint32_t selector,uint32_t value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_gte_owner_write_control(&boot->gte,context,selector,value);
    if (accepted) fprintf(stderr,"native_boot: GTE_CONTROL pc=%08x selector=%u value=%08x writes=%llu\n",
        context->pc,selector,value,(unsigned long long)boot->gte.write_count);
    return accepted;
}
static int cpu_write_gte_data(void *userdata,const MusashiCpuContext *context,uint32_t selector,uint32_t value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_gte_owner_write_data(&boot->gte,context,selector,value);
    if (accepted) fprintf(stderr,"native_boot: GTE_DATA_WRITE pc=%08x selector=%u value=%08x writes=%llu\n",
        context->pc,selector,value,(unsigned long long)boot->gte.data_write_count);
    return accepted;
}
static int cpu_read_gte_data(void *userdata,const MusashiCpuContext *context,uint32_t selector,uint32_t *value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_gte_owner_read_data(&boot->gte,context,selector,value);
    if (accepted) fprintf(stderr,"native_boot: GTE_DATA_READ pc=%08x selector=%u value=%08x reads=%llu\n",
        context->pc,selector,*value,(unsigned long long)boot->gte.data_read_count);
    return accepted;
}
static int cpu_read_control(void *userdata,const MusashiCpuContext *context,uint32_t selector,uint32_t *value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_gte_owner_read_control(&boot->gte,context,selector,value);
    if (accepted) fprintf(stderr,"native_boot: GTE_CONTROL_READ pc=%08x selector=%u value=%08x\n",
        context->pc,selector,*value);
    return accepted;
}
static int cpu_gte_command(void *userdata,const MusashiCpuContext *context,uint32_t word) {
    NativeBoot *boot=userdata;
    int accepted=musashi_gte_owner_command(&boot->gte,context,word);
    if (accepted) fprintf(stderr,"native_boot: GTE_COMMAND pc=%08x word=%08x commands=%llu\n",
        context->pc,word,(unsigned long long)boot->gte.command_count);
    return accepted;
}
static int image_read(void *userdata,uint32_t address,uint32_t *value) {
    return musashi_bios_exception_read32(&((NativeBoot *)userdata)->exception_image,address,value);
}
static int image_write(void *userdata,uint32_t address,uint32_t value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_bios_exception_write32(&boot->exception_image,address,value);
    if (accepted) fprintf(stderr,"native_boot: BIOS_IMAGE_WRITE address=%08x value=%08x writes=%llu dirty=%d\n",
        address,value,(unsigned long long)boot->exception_image.writes,boot->exception_image.dirty);
    return accepted;
}
static int image_table(void *userdata,uint32_t *value) {
    NativeBoot *boot=userdata;
    int accepted=musashi_bios_exception_table(&boot->exception_image,value);
    if (accepted) fprintf(stderr,"native_boot: BIOS_IMAGE_TABLE value=%08x generation=%llu\n",
        *value,(unsigned long long)boot->exception_image.generation);
    return accepted;
}
static int image_publish(void *userdata) {
    NativeBoot *boot=userdata;
    int accepted=musashi_bios_exception_publish(&boot->exception_image);
    fprintf(stderr,"native_boot: BIOS_IMAGE_PUBLISH accepted=%d generation=%llu variant=%u dirty=%d writes=%llu\n",
        accepted,(unsigned long long)boot->exception_image.generation,(unsigned)boot->exception_image.variant,
        boot->exception_image.dirty,(unsigned long long)boot->exception_image.writes);
    return accepted;
}
static int vsync_wait_raise_tick(NativeBoot *boot, const void *continuation) {
    MusashiCpuContext context;
    uint32_t tick = 0;
    if (!musashi_boot_cpu_context(continuation, MUSASHI_CPU_CONTEXT_SOURCE, &context) ||
        !context.gpr || context.pc < 0x800424e4u || context.pc >= 0x80042570u)
        return 1;
    if (!musashi_boot_read32(&boot->memory, 0x8006cbb8u, &tick))
        return 0;
    if (tick >= context.gpr[4])
        return 1;
    /* Retail 800424E4 polls 8006CBB8; 80042CE8 is the handler that increments
     * it. Latch I_STAT VBlank so the existing dispatcher runs that handler. */
    fprintf(stderr, "native_boot: VSYNC_WAIT_VBLANK tick=%u target=%u pc=%08x\n",
            tick, context.gpr[4], context.pc);
    return musashi_irq_controller_raise_vblank(&boot->irq.controller);
}

/* Opt-in refusal trace, off unless MUSASHI_TRACE_REFUSAL is set. Prints only:
 * the checkpoint's accept/refuse decision is unchanged either way. */
static int checkpoint_refuse(const void *continuation, const char *why) {
    MusashiCpuContext context;
    const char *trace = getenv("MUSASHI_TRACE_REFUSAL");
    if (continuation &&
        trace && trace[0] && trace[0] != '0' &&
        musashi_boot_cpu_context(continuation, MUSASHI_CPU_CONTEXT_SOURCE, &context))
        fprintf(stderr, "native_boot: CHECKPOINT_REFUSED pc=%08x why=%s\n", context.pc, why);
    return 0;
}

static int checkpoint(void *userdata, const void *continuation) {
    NativeBoot *boot = userdata;
    MusashiCpuContext context;
    if (!continuation) return 0;
    if (boot->continuation && boot->continuation != continuation) {
        /* Nested IRQ source function: keep the interrupted CPU identity and
         * do not dispatch while the owner pump is already delivering. */
        if (!(boot->irq.scheduler.pumping || boot->irq.scheduler.delivering))
            return checkpoint_refuse(continuation, "nested-identity");
        return musashi_device_epoch_sync(&boot->epoch);
    }
    boot->continuation = continuation;
    if (!boot->gte.initialized) {
        if (!musashi_boot_cpu_context(continuation,MUSASHI_CPU_CONTEXT_SOURCE,&context) ||
            !musashi_gte_owner_init(&boot->gte,boot->irq.cpu_status,epoch_owner,boot,context.identity))
            return checkpoint_refuse(continuation, "gte-init");
    }
    if (!musashi_device_epoch_sync(&boot->epoch)) return checkpoint_refuse(continuation, "epoch-sync");
    if (!boot->irq.scheduler.installed) return 1;
    if (boot->irq.scheduler.pumping || boot->irq.scheduler.delivering) return 1;
    if (!vsync_wait_raise_tick(boot, continuation)) return checkpoint_refuse(continuation, "vsync-wait");
    return musashi_psycross_irq_scheduler_dispatch_pending(&boot->irq.scheduler, continuation);
}

static int run_backup_unit(void *userdata, int32_t *guest_result) {
    NativeBoot *boot = userdata;
    Uint32 started = SDL_GetTicks();
    const void *continuation = boot->continuation;
    uint64_t epoch_started = boot->epoch.cycle;
    uint64_t source_started = boot->source_clock.cycles;
    if (!continuation || !guest_result || boot->irq.scheduler.pumping ||
        !musashi_bios_backup_unit_begin(&boot->backup_unit))
        return 0;
    for (;;) {
        int complete;
        if (!musashi_bios_backup_unit_poll(&boot->backup_unit, &complete, guest_result))
            return 0;
        if (complete) {
            fprintf(stderr, "native_boot: BU_CLOCK start=%llu end=%llu "
                    "source_start=%llu source_end=%llu\n",
                    (unsigned long long)epoch_started, (unsigned long long)boot->epoch.cycle,
                    (unsigned long long)source_started, (unsigned long long)boot->source_clock.cycles);
            fprintf(stderr, "native_boot: BU_RETURN result=%d memory_cards=DISCONNECTED "
                    "bu_return_port=%u bu_return_last_port=%u bu_return_flags=%02x%02x "
                    "sio_tx_bytes=%llu\n", (int)*guest_result,
                    (unsigned)boot->card.port, (unsigned)boot->card.last_port,
                    (unsigned)boot->card.flags[0], (unsigned)boot->card.flags[1],
                    (unsigned long long)boot->sio.transmitted_bytes);
            return 1;
        }
        /* The actual suspended game CPU survives the BIOS wait. Only a
         * real source edge and owner-thread IRQ handler can finish a card
         * request. Wall time limits observation; it never completes I/O. */
        if (boot->continuation != continuation || !musashi_device_epoch_sync(&boot->epoch) ||
            !musashi_psycross_irq_scheduler_dispatch_pending(&boot->irq.scheduler, continuation))
            return 0;
        if ((Uint32)(SDL_GetTicks() - started) >= 10000u) {
            fputs("native_boot: backup-unit wait observation timed out\n", stderr);
            return 0;
        }
        SDL_Delay(1);
    }
}

static int init_backup_unit(void *userdata,int32_t *guest_result) {
    NativeBoot *boot=userdata;int accepted;
    if (boot->host_service_depth) return 0;
    boot->host_service_depth++;
    accepted=run_backup_unit(userdata,guest_result);
    boot->host_service_depth--;
    return accepted;
}

static void console_bytes(void *userdata, const uint8_t *bytes, int32_t length) {
    (void)userdata;
    if (length > 0 && fwrite(bytes, 1, (size_t)length, stdout) != (size_t)length) {
        fputs("native_boot: console output failed\n", stderr);
        exit(2);
    }
}

static int source_irq_execute(void *userdata, MusashiBootMemory *memory, uint32_t target) {
    NativeBoot *boot = userdata;
    MusashiResetGraphPrefixStop stop = {0};
    MusashiResetGraphPrefixStatus status;
    status = musashi_boot_execute_source_function(memory, &boot->startup_devices,
        target, console_bytes, NULL, &stop);
    if (status != MUSASHI_RESETGRAPH_PREFIX_COMPLETE) {
        boot->irq.failed_target = (stop.target_address && stop.target_address != 0xffffffffu)
            ? stop.target_address : target;
        fprintf(stderr, "native_boot: SOURCE_IRQ_EXECUTE target=%08x stop=%08x status=%d\n",
                (unsigned)target, (unsigned)stop.target_address, (int)status);
        return 0;
    }
    return 1;
}

/* The runner accepts IRQ registers and the owned Timer1 count. A refused
 * access is fatal, never a synthesized register value or ignored write. */
static uint16_t irq_read16(void *userdata, uint32_t address) {
    NativeBoot *boot = userdata;
    uint16_t value;
    if (!(address == 0x1f801110u ?
          musashi_scanline_timer_read16(&boot->timer1, address, &value) :
          musashi_irq_controller_read16(&boot->irq.controller, address, &value))) {
        fprintf(stderr, "native_boot: unsupported IRQ read %08x\n", (unsigned)address);
        exit(2);
    }
    return value;
}

static void irq_write16(void *userdata, uint32_t address, uint16_t value) {
    NativeBoot *boot = userdata;
    if (!musashi_irq_controller_write16(&boot->irq.controller, address, value)) {
        fprintf(stderr, "native_boot: unsupported IRQ write %08x\n", (unsigned)address);
        exit(2);
    }
    if (boot->gpu_trace)
        fprintf(stderr, "native_boot: GPU_TRACE address=%08x width=2 value=%08x\n",
                (unsigned)address, (unsigned)value);
}

static int dma_irq_read32(void *userdata, uint32_t address, uint32_t *value) {
    NativeBoot *boot = userdata;
    return musashi_dma_controller_read32(&boot->dma, address, value);
}

static int dma_irq_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    int accepted = musashi_dma_controller_write32(&boot->dma, address, value);
    if (accepted)
        fprintf(stderr, "native_boot: DMA_IRQ_DICR address=%08x value=%08x dicr=%08x\n",
                (unsigned)address, (unsigned)value, (unsigned)boot->dma.interrupt);
    return accepted;
}

static void control_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    if (address == 0x1f801020u) {
        /* MEMCTRL COMMON_DELAY is retained as a complete word, matching
         * psxhw.cc's default register write/read. The inspected reference
         * does not derive CD command latency from this latch. */
        boot->common_delay = value;
        boot->common_delay_written = 1;
        return;
    }
    if (!musashi_dma_controller_write32(&boot->dma, address, value) &&
        !musashi_scanline_timer_write32(&boot->timer1, address, value)) {
        fprintf(stderr, "native_boot: unsupported control write %08x=%08x "
                "DPCR=%08x IRQ_installed=%d menu=NOT_REACHED\n",
                (unsigned)address, (unsigned)value, (unsigned)boot->dma.control,
                boot->irq.scheduler.installed);
        exit(2);
    }
}

static uint32_t gpu_read32(void *userdata, uint32_t address) {
    NativeBoot *boot = userdata;
    uint32_t value;
    int accepted = (address==0x1f8010f0u || address==0x1f8010f4u) ?
        musashi_dma_controller_read32(&boot->dma,address,&value) :
        gpu_io_read32(boot,address,&value);
    if (!accepted) {
        fprintf(stderr, "native_boot: unsupported GPU read %08x menu=NOT_REACHED\n",
                (unsigned)address);
        exit(2);
    }
    return value;
}

static void gpu_write32(void *userdata, uint32_t address, uint32_t value) {
    NativeBoot *boot = userdata;
    int accepted = (address==0x1f8010f0u || address==0x1f8010f4u) ?
        musashi_dma_controller_write32(&boot->dma,address,value) :
        gpu_io_write32(boot,address,value);
    if (!accepted) {
        fprintf(stderr, "native_boot: unsupported GPU write %08x=%08x menu=NOT_REACHED\n",
                (unsigned)address, (unsigned)value);
        exit(2);
    }
    if (boot->gpu_trace && (address==0x1f8010f0u || address==0x1f8010f4u))
        fprintf(stderr, "native_boot: GPU_TRACE address=%08x width=4 value=%08x\n",
                (unsigned)address, (unsigned)value);
}

static int gpu_cw(void *userdata, uint32_t command, int32_t *result) {
    NativeBoot *boot = userdata;
    uint32_t status;
    /* SCPH BIOS A0:49 calls BFC04138 before submitting one GP0 word.
     * The observed boot takes its DMA-off, immediately-ready branch. Other
     * DMA/wait paths remain explicit refusal until transfer ownership exists. */
    if (!result || !musashi_gpu_controller_read32(&boot->gpu, 0x1f801814u, &status) ||
        (status & 0x60000000u) || !(status & 0x10000000u) ||
        !musashi_gpu_controller_write32(&boot->gpu, 0x1f801810u, command))
        return 0;
    *result = 0;
    boot->gpu_trace = getenv("MUSASHI_NATIVE_GPU_TRACE") != NULL;
    if (boot->gpu_trace)
        fprintf(stderr, "native_boot: GPU_TRACE address=1f801810 width=4 value=%08x\n",
                (unsigned)command);
    return 1;
}

static void observe_spu_stage(NativeBoot *boot, uint32_t pc) {
    MusashiSpuCdAudioSnapshot state;
    uint32_t handle, guard;
    unsigned i;
    if (!boot->spu || !musashi_spu_cd_audio_snapshot(boot->spu, &state) ||
        !musashi_boot_read32(&boot->memory, 0x8006b0e0u, &handle) ||
        !musashi_boot_read32(&boot->memory, 0x8006b548u, &guard)) {
        fputs("native_boot: SPU_STAGE refused\n", stderr);
        return;
    }
    fprintf(stderr, "native_boot: SPU_STAGE pc=%08x cycle=%llu samples=%llu "
            "main_left=%04x main_right=%04x control=%04x manual_halfwords=%llu "
            "cursor=%05x transfer_address=%04x transfer_control=%04x "
            "event_handle=%08x event_guard=%08x faulted=%d "
            "manual_policy=SYNCHRONOUS_SOURCE_MODEL key_policy=POST_FRAME "
            "hardware_subphase=UNPROVEN\n", pc,
            (unsigned long long)state.cycle, (unsigned long long)state.sample_index,
            (unsigned)(uint16_t)state.main_left_current,
            (unsigned)(uint16_t)state.main_right_current, state.control,
            (unsigned long long)state.manual_halfwords, state.transfer_cursor,
            state.transfer_address, state.transfer_control, handle, guard, state.faulted);
    if (pc == 0x8002c984u || pc == 0x8002c98cu || pc == 0x800101fcu) {
        MusashiSpuReverbSnapshot reverb;
        if (!musashi_spu_cd_audio_reverb_snapshot(boot->spu, &reverb))
            fputs("native_boot: SPU_REVERB refused\n", stderr);
        else {
            fprintf(stderr, "native_boot: SPU_REVERB pc=%08x base=%04x enabled=%d "
                    "wet_left=%04x wet_right=%04x cursor=%05x eon=%06x next_channel=%u "
                    "frames=%llu processed_left=%llu processed_right=%llu ram_reads=%llu "
                    "ram_writes=%llu unknown_reads=%llu unsupported_steps=%llu "
                    "unknown_history_left=%llu unknown_history_right=%llu bootstrap_halfwords=%llu coefficients=",
                    pc, reverb.base, reverb.enabled, (unsigned)(uint16_t)reverb.wet_left,
                    (unsigned)(uint16_t)reverb.wet_right, reverb.cursor, reverb.eon,
                    reverb.next_channel, (unsigned long long)reverb.frames,
                    (unsigned long long)reverb.processed_left, (unsigned long long)reverb.processed_right,
                    (unsigned long long)reverb.ram_reads, (unsigned long long)reverb.ram_writes,
                    (unsigned long long)reverb.unknown_reads, (unsigned long long)reverb.unsupported_steps,
                    (unsigned long long)reverb.unknown_history_left, (unsigned long long)reverb.unknown_history_right,
                    (unsigned long long)state.bootstrap_halfwords);
            for (i=0;i<32;++i) fprintf(stderr, "%s%04x", i ? "," : "", reverb.coefficients[i]);
            fputc('\n', stderr);
        }
    }
    if (state.manual_halfwords) {
        uint8_t bytes[16];
        int valid = musashi_spu_cd_audio_copy_ram(boot->spu, 0x1000u, bytes, sizeof(bytes));
        fprintf(stderr, "native_boot: SPU_RAM pc=%08x offset=01000 valid=%d bytes=", pc, valid);
        if (valid) for (i = 0; i < sizeof(bytes); ++i) fprintf(stderr, "%02x", bytes[i]);
        fputc('\n', stderr);
    }
    if (pc == 0x8002c90cu) {
        for (i = 0; i < 24; ++i) {
            MusashiSpuVoiceSnapshot voice;
            unsigned j;
            if (!musashi_spu_cd_audio_voice_snapshot(boot->spu, i, &voice)) {
                fprintf(stderr, "native_boot: SPU_VOICE index=%u refused=1\n", i);
                continue;
            }
            fprintf(stderr, "native_boot: SPU_VOICE index=%u phase=%u envelope=%d "
                    "cursor=%05x repeat=%05x blocks=%llu decoded=%llu "
                    "pending_on=%d pending_off=%d endx=%d regs=", i, voice.phase,
                    voice.envelope, voice.cursor, voice.repeat,
                    (unsigned long long)voice.decoded_blocks,
                    (unsigned long long)voice.decoded_samples,
                    voice.pending_on, voice.pending_off, voice.endx);
            for (j = 0; j < 8; ++j) fprintf(stderr, "%s%04x", j ? "," : "", voice.registers[j]);
            fputc('\n', stderr);
        }
    }
}

/* Record one CPU state per distinct (pc, caller) pair. The formatter stops the
 * fast path at each recovered call gate, and the sampled step trace covers the
 * earliest instructions; both feed this record, so every trace line is unique
 * and the caller registers stay auditable. */
static void trace_cpu_state(uint32_t pc, uint32_t npc, uint32_t hi, uint32_t lo,
                            const uint32_t *r) {
    static uint32_t gates[512];
    static uint32_t callers[512];
    static unsigned recorded;
    unsigned slot, i;
    for (slot = 0; slot < recorded; ++slot)
        if (gates[slot] == pc && callers[slot] == r[31]) return;
    if (recorded >= sizeof(gates) / sizeof(gates[0])) return;
    gates[recorded] = pc;
    callers[recorded] = r[31];
    ++recorded;
    fprintf(stderr, "native_boot: CPU_TRACE pc=%08x npc=%08x hi=%08x lo=%08x regs=",
            (unsigned)pc, (unsigned)npc, (unsigned)hi, (unsigned)lo);
    for (i = 0; i < 32; i++)
        fprintf(stderr, "%s%08x", i ? "," : "", (unsigned)r[i]);
    fputc('\n', stderr);
}

static void observe_entry(void *userdata, const MusashiEntryCpuSnapshot *cpu) {
    NativeBoot *boot = userdata;
    unsigned i;
    trace_cpu_state(cpu->pc, cpu->npc, cpu->hi, cpu->lo, cpu->r);
    if (cpu->pc == 0x800cf104u && boot->opening_overlay_ready) {
        const char *preview=getenv("MUSASHI_PAUSE_AT_START_SCREEN");
        uint16_t state;
        uint32_t prompt_visible;
        if (preview && preview[0]=='1' &&
            musashi_boot_read16(&boot->memory,0x800b99e4u,&state) && state==4u &&
            ++boot->start_preview_frames>=30u &&
            musashi_boot_read32(&boot->memory,0x800ec694u,&prompt_visible) && prompt_visible==1u) {
            /* Host inspection stop after natural menu frames. This never
             * changes a guest PC, input, state flag, or rendering command. */
            boot->start_preview_paused=1;
            fprintf(stderr,"native_boot: MENU_PREVIEW paused=1 source_pc=800cf104 frames=%u\n",
                    boot->start_preview_frames);
            host_stop_signal=SIGTERM;
        }
    }
    if (cpu->pc == 0x80053218u || cpu->pc == 0x80014690u ||
        cpu->pc == 0x80053178u || cpu->pc == 0x80014680u ||
        cpu->pc == 0x8005283cu || cpu->pc == 0x80052d00u ||
        cpu->pc == 0x80052d80u || cpu->pc == 0x80052becu ||
        cpu->pc == 0x80052c74u || cpu->pc == 0x80014650u) {
        static const uint32_t addresses[] = {
            0x800ae618u,0x800ae61cu,0x800ae7f8u,0x800ae820u,
            0x800ae824u,0x800a6438u,0x800a643cu,0x800a6440u,
            0x800a6548u,0x800c7c70u,0x800c7c74u,0x800c7c88u,
            0x800794e0u,0x800794e4u,0x800a5e50u,
            0x800c73d0u,0x800c6dc8u,0x800ae7e8u
        };
        fprintf(stderr,"native_boot: PROJECTION_SOURCE pc=%08x sp=%08x ra=%08x "
                "v0=%08x a0=%08x a1=%08x hi=%08x lo=%08x\n",
                cpu->pc,cpu->r[29],cpu->r[31],cpu->r[2],cpu->r[4],cpu->r[5],cpu->hi,cpu->lo);
        for (i=0;i<sizeof(addresses)/sizeof(addresses[0]);++i) {
            uint32_t value=0;
            int valid=musashi_boot_read32(&boot->memory,addresses[i],&value);
            fprintf(stderr,"native_boot: PROJECTION_RAM pc=%08x address=%08x valid=%d value=%08x\n",
                    cpu->pc,addresses[i],valid,value);
        }
    }
    if (cpu->pc == 0x80059888u) {
        uint16_t rect[4]={0};
        int valid=1;
        for (i=0;i<4u;++i)
            valid=musashi_boot_read16(&boot->memory,cpu->r[4]+i*2u,&rect[i]) && valid;
        fprintf(stderr,"native_boot: CLEAR_SOURCE pc=%08x sp=%08x ra=%08x rect=%08x "
                "valid=%d xywh=%04x,%04x,%04x,%04x rgb=%08x,%08x,%08x\n",
                cpu->pc,cpu->r[29],cpu->r[31],cpu->r[4],valid,
                rect[0],rect[1],rect[2],rect[3],cpu->r[5],cpu->r[6],cpu->r[7]);
    }
    if (cpu->pc == 0x800101c8u) boot->graphics_returned = 1;
    if (cpu->pc == 0x8005d8b4u || cpu->pc == 0x800101e4u) observe_input_state(boot, cpu->pc);
    if (cpu->pc == 0x8005d804u || cpu->pc == 0x8005d858u ||
        cpu->pc == 0x8005dc50u || cpu->pc == 0x8005dc88u) {
        static uint64_t n;
        uint32_t slot = 0, stage = 0, active = 0, counter = 0;
        uint8_t tap = 0xff, mode = 0xff;
        uint8_t *pad = musashi_boot_ram_span(&boot->memory, 0x80078a48u, 0x51u);
        (void)musashi_boot_read32(&boot->memory, 0x800729b4u, &slot);
        (void)musashi_boot_read32(&boot->memory, 0x800729a0u, &stage);
        (void)musashi_boot_read32(&boot->memory, 0x800729acu, &active);
        (void)musashi_boot_read32(&boot->memory, 0x8007299cu, &counter);
        if (pad) { tap = pad[0x50]; mode = pad[0x46]; }
        if (log_sample(&n, 16u, 4096u))
            fprintf(stderr, "native_boot: TAP_PATH pc=%08x v0=%08x a0=%08x "
                    "29B4=%08x 29A0=%08x 29AC=%08x 299C=%08x tap50=%02x mode46=%02x\n",
                    cpu->pc, cpu->r[2], cpu->r[4], slot, stage, active, counter,
                    tap, mode);
    }
    {
        static uint64_t n;
        if (log_sample(&n, 4u, 65536u))
            trace_cpu_state(cpu->pc, cpu->npc, cpu->hi, cpu->lo, cpu->r);
    }
    if (cpu->pc == 0x80034cd0u || cpu->pc == 0x800101fcu) {
        uint32_t tracks = cpu->r[2];
        const uint8_t *toc = musashi_boot_ram_span(&boot->memory, 0x800c7d30u, 20);
        int valid = toc != NULL;
        if (cpu->pc == 0x800101fcu)
            valid = valid && musashi_boot_read32(&boot->memory, 0x800a5bc8u, &tracks);
        fprintf(stderr, "native_boot: SOUND_TOC pc=%08x valid=%d tracks=%u address=800c7d30 bytes=",
                cpu->pc, valid, tracks);
        if (valid) for (i=0;i<20;++i) fprintf(stderr, "%02x", toc[i]);
        fputc('\n', stderr);
    }
    if (cpu->pc == 0x80045cb8u) {
        const uint8_t *loc=musashi_boot_ram_span(&boot->memory,cpu->r[29]+0x10u,3);
        fprintf(stderr,"native_boot: CD_SECTOR_REQUEST valid=%d count=%u destination=%08x location=",
                loc != NULL,cpu->r[17],cpu->r[16]);
        if (loc) for (i=0;i<3;++i) fprintf(stderr,"%02x",loc[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x80045698u) {
        const uint8_t *pvd = musashi_boot_ram_span(&boot->memory, cpu->r[16], 2048);
        uint8_t raw[MUSASHI_DISC_RAW_SECTOR_SIZE], digest[SHA256_DIGEST_LENGTH];
        int valid = pvd != NULL;
        /* Read-only verification after the source read returns. The disc
         * comparison never supplies bytes to guest RAM or alters CD state. */
        int exact = valid && boot->media &&
            musashi_disc_media_read_sector(boot->media, 16, raw, sizeof(raw)) &&
            memcmp(pvd, raw+24, 2048) == 0;
        fprintf(stderr,"native_boot: PVD_RETURN pc=%08x result=%08x address=%08x valid=%d bytes=2048 retail_exact=%d sha256=",
                cpu->pc,cpu->r[2],cpu->r[16],valid,exact);
        if (valid && SHA256(pvd,2048,digest))
            for (i=0;i<sizeof(digest);++i) fprintf(stderr,"%02x",digest[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x80045744u) {
        uint32_t lba = 0;
        const uint8_t *data = musashi_boot_ram_span(&boot->memory,cpu->r[16],2048);
        uint8_t raw[MUSASHI_DISC_RAW_SECTOR_SIZE],digest[SHA256_DIGEST_LENGTH];
        int valid = data && musashi_boot_read32(&boot->memory,cpu->r[29]+0x18u,&lba);
        int exact = valid && boot->media &&
            musashi_disc_media_read_sector(boot->media,lba,raw,sizeof(raw)) &&
            memcmp(data,raw+24,2048) == 0;
        fprintf(stderr,"native_boot: PATH_TABLE_READ_RETURN result=%08x lba=%u address=%08x valid=%d bytes=2048 retail_exact=%d sha256=",
                cpu->r[2],lba,cpu->r[16],valid,exact);
        if (valid && SHA256(data,2048,digest))
            for (i=0;i<sizeof(digest);++i) fprintf(stderr,"%02x",digest[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x80045918u) {
        const uint8_t *record = musashi_boot_ram_span(&boot->memory,0x80076a00u,44);
        fprintf(stderr,"native_boot: PATH_TABLE_PARSE_RETURN result=%08x records=%u first_record=",
                cpu->r[2],cpu->r[7]);
        if (record) for (i=0;i<44;++i) fprintf(stderr,"%02x",record[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x8004544cu)
        fprintf(stderr,"native_boot: DIRECTORY_LOOKUP_RETURN result=%08x\n",cpu->r[2]);
    if (cpu->pc == 0x80045a50u) {
        uint32_t lba = 0;
        const uint8_t *data = musashi_boot_ram_span(&boot->memory,cpu->r[16],2048);
        uint8_t raw[MUSASHI_DISC_RAW_SECTOR_SIZE],digest[SHA256_DIGEST_LENGTH];
        /* The source directory ordinal selects the live path-cache extent.
         * This comparison is diagnostic only, after the real CD read. */
        int valid = data && cpu->r[22] >= 1u && cpu->r[22] <= 128u &&
            musashi_boot_read32(&boot->memory,0x800769dcu+44u*cpu->r[22],&lba);
        int exact = valid && boot->media &&
            musashi_disc_media_read_sector(boot->media,lba,raw,sizeof(raw)) &&
            memcmp(data,raw+24,2048) == 0;
        fprintf(stderr,"native_boot: DIRECTORY_READ_RETURN result=%08x ordinal=%u lba=%u address=%08x valid=%d bytes=2048 retail_exact=%d sha256=",
                cpu->r[2],cpu->r[22],lba,cpu->r[16],valid,exact);
        if (valid && SHA256(data,2048,digest))
            for (i=0;i<sizeof(digest);++i) fprintf(stderr,"%02x",digest[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x80045c14u) {
        unsigned record_index;
        fprintf(stderr,"native_boot: DIRECTORY_PARSE_END ordinal=%u records=%u cursor=%08x\n",
                cpu->r[22],cpu->r[18],cpu->r[16]);
        for (record_index=0;record_index<cpu->r[18] && record_index<64u;++record_index) {
            const uint8_t *record=musashi_boot_ram_span(&boot->memory,0x80076400u+24u*record_index,24);
            fprintf(stderr,"native_boot: DIRECTORY_RECORD index=%u valid=%d bytes=",record_index,record!=NULL);
            if (record) for (i=0;i<24;++i) fprintf(stderr,"%02x",record[i]);
            fputc('\n',stderr);
        }
    }
    if (cpu->pc == 0x80019768u || cpu->pc == 0x800197ccu) {
        uint32_t output=cpu->pc==0x80019768u ? cpu->r[16] : cpu->r[16]+cpu->r[18];
        const uint8_t *name=musashi_boot_ram_span(&boot->memory,output-20u,20);
        const uint8_t *record=musashi_boot_ram_span(&boot->memory,output,24);
        fprintf(stderr,"native_boot: FILE_LOOKUP_RETURN required=%d index=%u result=%08x output=%08x name_hex=",
                cpu->pc==0x800197ccu,cpu->r[21],cpu->r[2],output);
        if (name) for (i=0;i<20;++i) fprintf(stderr,"%02x",name[i]);
        fprintf(stderr," record_valid=%d record=",record!=NULL);
        if (record) for (i=0;i<24;++i) fprintf(stderr,"%02x",record[i]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x800525dcu || cpu->pc == 0x800526a8u || cpu->pc == 0x800526fcu) {
        uint16_t callback_guard=0;
        uint32_t stackarg=0;
        int readable=musashi_boot_read16(&boot->memory,0x8006bafcu,&callback_guard) &&
            musashi_boot_read32(&boot->memory,cpu->r[29]+0x10u,&stackarg);
        fprintf(stderr,"native_boot: DRAW_SOURCE pc=%08x a0=%08x a1=%08x "
                "a2=%08x a3=%08x sp=%08x ra=%08x v0=%08x stack10=%08x "
                "readable=%d callback_guard=%u gpu_reset_sequence=%llu\n",
                cpu->pc,cpu->r[4],cpu->r[5],cpu->r[6],cpu->r[7],cpu->r[29],
                cpu->r[31],cpu->r[2],stackarg,readable,(unsigned)callback_guard,
                (unsigned long long)boot->gpu_reset_sequence);
    }
    if (cpu->pc == 0x80059df4u) {
        uint32_t tag=0, word=0;
        unsigned n;
        int valid=musashi_boot_read32(&boot->memory,cpu->r[5],&tag);
        unsigned words=valid ? (tag>>24)+1u : 0;
        fprintf(stderr,"native_boot: DRAW_PACKET address=%08x tag=%08x words=%u valid=%d data=",
                cpu->r[5],tag,words,valid);
        if (words<=17u) for (n=0;n<words;++n) {
            if (!musashi_boot_read32(&boot->memory,cpu->r[5]+4u*n,&word)) break;
            fprintf(stderr,"%s%08x",n ? "," : "",word);
        }
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x8005b870u || cpu->pc == 0x8005b720u || cpu->pc == 0x8005b730u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr,"native_boot: DRAW_DEVICE pc=%08x address=%08x a0=%08x "
                    "v1=%08x sp=%08x ra=%08x\n",cpu->pc,cpu->r[2],cpu->r[4],
                    cpu->r[3],cpu->r[29],cpu->r[31]);
    }
    if (cpu->pc == 0x80059dfcu) {
        fprintf(stderr,"native_boot: DRAW_QUEUE_RETURN pc=%08x v0=%08x sp=%08x "
                "ra=%08x I_MASK=%04x\n",cpu->pc,cpu->r[2],cpu->r[29],cpu->r[31],
                boot->irq.controller.mask);
        observe_gpu_dma(boot,"SOURCE_QUEUE_RETURN");
    }
    if (cpu->pc == 0x8005b690u) {
        static uint64_t gp1_logs;
        const uint8_t *cache=musashi_boot_ram_span(&boot->memory,
            0x80078874u+(cpu->r[4]>>24),1);
        if (gp1_logs < 8u || (gp1_logs % 4096u) == 0u)
            fprintf(stderr,"native_boot: DISPLAY_GP1 pc=%08x word=%08x address=%08x "
                    "sp=%08x ra=%08x cache_valid=%d cache_before=%02x n=%llu\n",
                    cpu->pc,cpu->r[4],cpu->r[2],cpu->r[29],cpu->r[31],cache!=NULL,
                    cache ? *cache : 0, (unsigned long long)gp1_logs);
        if (gp1_logs != UINT64_MAX) ++gp1_logs;
    }
    if (cpu->pc == 0x8005279cu) {
        const uint8_t *env=musashi_boot_ram_span(&boot->memory,0x800a6498u,20);
        const uint8_t *cache=musashi_boot_ram_span(&boot->memory,0x800727f4u,20);
        fprintf(stderr,"native_boot: DISPLAY_SOURCE_RETURN pc=%08x v0=%08x sp=%08x "
                "ra=%08x env_valid=%d cache_valid=%d cache_equal=%d cache=",
                cpu->pc,cpu->r[2],cpu->r[29],cpu->r[31],env!=NULL,cache!=NULL,
                env && cache && !memcmp(env,cache,20));
        if (cache) for (unsigned j=0;j<20;++j) fprintf(stderr,"%02x",cache[j]);
        fputc('\n',stderr);
    }
    if (cpu->pc == 0x80014948u || cpu->pc == 0x80014248u)
        fprintf(stderr,"native_boot: HEAP_SOURCE_RETURN pc=%08x v0=%08x "
                "sp=%08x ra=%08x guest_irq_enabled=%d\n",
                cpu->pc,cpu->r[2],cpu->r[29],cpu->r[31],
                guest_irq_enabled(boot));
    if (cpu->pc == 0x800197ecu) {
        fprintf(stderr,"native_boot: REQUIRED_FILE_SEARCHES_RETURN count=%u\n",cpu->r[21]);
        if (!boot->list_tail_captured) {
            const uint8_t *tail=musashi_boot_ram_span(&boot->memory,0x80180e40u,448);
            if (tail) {
                memcpy(boot->list_tail_before,tail,448);
                boot->list_tail_captured=1;
            }
        }
    }
    if (cpu->pc == 0x80010f80u) {
        static uint64_t n;
        if (log_sample(&n, 4u, 4096u))
            fprintf(stderr, "native_boot: SCENE_INIT pc=80010f80 v0=%08x v1=%08x a0=%08x "
                    "sp=%08x ra=%08x overlay7=%d\n",
                    cpu->r[2], cpu->r[3], cpu->r[4], cpu->r[29], cpu->r[31],
                    boot->opening_overlay_ready);
        (void)select_opening_overlay(boot);
    }
    if (cpu->pc == 0x800ceec8u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_JALR pc=800ceec8 v0=%08x v1=%08x "
                    "a0=%08x sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[3], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800ceefcu) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_TABLE0 pc=800ceefc v0=%08x a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800cef60u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_TABLE1 pc=800cef60 v0=%08x a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800cef94u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_TABLE2 pc=800cef94 v0=%08x a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800ceff8u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_TABLE3 pc=800ceff8 v0=%08x a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800cf02cu) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_CF02C pc=800cf02c v0=%08x a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800cf068u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_OPDEMO pc=800cf068 a0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[4], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800118acu) {
        static uint64_t n;
        uint16_t a3b4 = 0, a3b6 = 0, a3b4_c = 0, a3b6_c = 0;
        (void)musashi_boot_read16(&boot->memory, 0x800b99e4u, &a3b4);
        (void)musashi_boot_read16(&boot->memory, 0x800b99e6u, &a3b6);
        (void)musashi_boot_read16(&boot->memory, 0x800c99e4u, &a3b4_c);
        (void)musashi_boot_read16(&boot->memory, 0x800c99e6u, &a3b6_c);
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: SCENE_A3B4 pc=800118ac a3b4=%04x a3b6=%04x "
                    "c99e4=%04x c99e6=%04x ra=%08x\n",
                    a3b4, a3b6, a3b4_c, a3b6_c, cpu->r[31]);
    }
    if (cpu->pc == 0x80011818u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: SCENE_SWITCH pc=80011818 a0=%08x "
                    "ra=%08x\n", cpu->r[4], cpu->r[31]);
    }
    if (cpu->pc == 0x800110ccu) {
        static uint64_t n;
        uint32_t w0 = 0, w1 = 0;
        boot->title_scene_reached = 1;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: TITLE_SCENE pc=800110cc ra=%08x\n",
                    cpu->r[31]);
        (void)musashi_boot_read32(&boot->memory, 0x800cedfcu, &w0);
        (void)musashi_boot_read32(&boot->memory, 0x800cee00u, &w1);
        if (w0 == 0x3c03800cu && w1 == 0x946399f0u)
            musashi_boot_select_overlay_0010_words(1);
    }
    if (cpu->pc == 0x8001125cu) {
        static int selected_0010;
        uint32_t w0 = 0, w1 = 0;
        (void)musashi_boot_read32(&boot->memory, 0x800cedfcu, &w0);
        (void)musashi_boot_read32(&boot->memory, 0x800cee00u, &w1);
        if (!selected_0010 && w0 == 0x3c03800cu && w1 == 0x946399f0u) {
            selected_0010 = 1;
            musashi_boot_select_overlay_0010_words(1);
            fprintf(stderr, "native_boot: OVERLAY_SELECT member=10 dest=800cedf8 "
                    "reason=8001125c signature\n");
        }
    }
    if (cpu->pc == 0x80019a24u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: TITLE_LOAD pc=80019a24 a0=%08x a1=%08x "
                    "ra=%08x\n", cpu->r[4], cpu->r[5], cpu->r[31]);
    }
    if (cpu->pc == 0x800cf3b0u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_START pc=800cf3b0 v0=%08x "
                    "sp=%08x ra=%08x\n",
                    cpu->r[2], cpu->r[29], cpu->r[31]);
    }
    if (cpu->pc == 0x800cef94u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_PAD800 pc=800cef94 a0=%08x "
                    "v0=%08x ra=%08x\n",
                    cpu->r[4], cpu->r[2], cpu->r[31]);
    }
    if (cpu->pc == 0x800167b8u && cpu->r[4] == 4u) {
        static uint64_t n;
        uint16_t held = 0, a3b4 = 0;
        (void)musashi_boot_read16(&boot->memory, 0x80078dd2u, &held);
        (void)musashi_boot_read16(&boot->memory, 0x800b99e4u, &a3b4);
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: PAD14CAC_OK pc=800167b8 a0=4 "
                    "8DD2=%04x a3b4=%04x ra=%08x\n",
                    held, a3b4, cpu->r[31]);
    }
    if (cpu->pc == 0x800cf3d4u) {
        static uint64_t n;
        uint32_t flag=0, id=0, held=0, edge=0;
        uint8_t *type=musashi_boot_ram_span(&boot->memory,0x80088d98u,1);
        (void)musashi_boot_read32(&boot->memory,0x800c99e4u,&flag);
        (void)musashi_boot_read32(&boot->memory,0x80088dc8u,&held);
        (void)musashi_boot_read32(&boot->memory,0x80088dd0u,&edge);
        (void)musashi_boot_read32(&boot->memory,0x80088d98u,&id);
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: OVERLAY_START_BITS pc=800cf3d4 s0=%08x "
                    "v0=%08x type=%02x 8DCA=%04x 8DD2=%04x C99E4=%04x C99E6=%04x "
                    "analog_mode=%d\n",
                    cpu->r[16], cpu->r[2], type?*type:0xffu,
                    (unsigned)((held>>16)&0xffffu), (unsigned)((edge>>16)&0xffffu),
                    (unsigned)(flag&0xffffu), (unsigned)((flag>>16)&0xffffu),
                    boot->sio.analog_mode);
    }
    if (cpu->pc == 0x80014b08u) {
        static uint64_t n;
        if (log_sample(&n, 8u, 4096u))
            fprintf(stderr, "native_boot: PAD149E0_RET pc=80014b08 v0=%08x "
                    "s0=%08x\n", cpu->r[2], cpu->r[16]);
    }
    if (cpu->pc == 0x8001aa98u)
        fprintf(stderr, "native_boot: FILE_STUB pc=8001aa98 a0=%08x ra=%08x\n",
                cpu->r[4], cpu->r[31]);
    if (cpu->pc == 0x80019b30u) {
        uint32_t mode=0, complete=0, expected=0, callback=0, cursor=0;
        uint8_t *aef4=musashi_boot_ram_span(&boot->memory,0x8006aef4u,1);
        (void)musashi_boot_read32(&boot->memory,0x800ae6f8u,&mode);
        (void)musashi_boot_read32(&boot->memory,0x800ae74cu,&complete);
        (void)musashi_boot_read32(&boot->memory,0x800ae7acu,&expected);
        (void)musashi_boot_read32(&boot->memory,0x8006cc88u,&callback);
        (void)musashi_boot_read32(&boot->memory,0x800a46c8u,&cursor);
        fprintf(stderr,"native_boot: LIST_STATE state=%u target=%08x mode=%u complete=%u expected=%u cb=%08x cursor=%08x aef4=%02x\n",
                cpu->r[3],cpu->r[2],mode,complete,expected,callback,cursor,aef4?*aef4:0xffu);
    }
    if (cpu->pc == 0x8002fc64u || cpu->pc == 0x8002fd10u) {
        uint32_t cursor=0;
        uint8_t *aef4=musashi_boot_ram_span(&boot->memory,0x8006aef4u,1);
        (void)musashi_boot_read32(&boot->memory,0x800a46c8u,&cursor);
        fprintf(stderr,"native_boot: PAC_SPU pc=%08x a0=%08x a1=%08x v0=%08x cursor=%08x aef4=%02x\n",
                cpu->pc,cpu->r[4],cpu->r[5],cpu->r[2],cursor,aef4?*aef4:0xffu);
    }
    if (cpu->pc == 0x80019804u) {
        fprintf(stderr,"native_boot: LIST_REQUEST_RETURN result=%08x\n",cpu->r[2]);
        if (cpu->r[2]) {
            const uint8_t *data=musashi_boot_ram_span(&boot->memory,0x80180000u,0xe40u);
            uint8_t raw[MUSASHI_DISC_RAW_SECTOR_SIZE],digest[SHA256_DIGEST_LENGTH];
            /* Read-only comparison against the source's actual E40 request.
             * These media reads never populate guest RAM or CD state. */
            int exact=data && boot->media &&
                musashi_disc_media_read_sector(boot->media,227,raw,sizeof(raw)) &&
                memcmp(data,raw+24,2048)==0 &&
                musashi_disc_media_read_sector(boot->media,228,raw,sizeof(raw)) &&
                memcmp(data+2048,raw+24,0xe40u-2048)==0;
            fprintf(stderr,"native_boot: LIST_PAYLOAD address=80180000 bytes=3648 valid=%d retail_exact=%d sha256=",data!=NULL,exact);
            if (data && SHA256(data,0xe40u,digest))
                for (i=0;i<sizeof(digest);++i) fprintf(stderr,"%02x",digest[i]);
            fputc('\n',stderr);
            const uint8_t *tail=musashi_boot_ram_span(&boot->memory,0x80180e40u,448);
            fprintf(stderr,"native_boot: LIST_TAIL address=80180e40 bytes=448 captured=%d unchanged=%d\n",
                    boot->list_tail_captured,boot->list_tail_captured && tail &&
                    memcmp(tail,boot->list_tail_before,448)==0);
        }
    }
    if (cpu->pc == 0x800198fcu) {
        unsigned record_index;
        fprintf(stderr,"native_boot: LIST_METADATA_PARSE_END groups=%u records=%u cursor=%08x source_records=%u\n",
                cpu->r[21],cpu->r[30],cpu->r[22],cpu->r[23]);
        for (record_index=0;record_index<cpu->r[30] && record_index<456u;++record_index) {
            const uint8_t *record=musashi_boot_ram_span(&boot->memory,0x800ae830u+8u*record_index,8);
            fprintf(stderr,"native_boot: ARCHIVE_MEMBER index=%u valid=%d bytes=",record_index,record!=NULL);
            if (record) for (i=0;i<8;++i) fprintf(stderr,"%02x",record[i]);
            fputc('\n',stderr);
        }
    }
    if (cpu->pc == 0x80010204u)
        fputs("native_boot: FILE_INITIALIZER_RETURN pc=80010204\n",stderr);
    if (cpu->pc == 0x8002c8f4u || cpu->pc == 0x8002c904u || cpu->pc == 0x8002c90cu ||
        cpu->pc == 0x8002c974u || cpu->pc == 0x8002c984u || cpu->pc == 0x8002c98cu ||
        cpu->pc == 0x800101fcu)
        observe_spu_stage(boot, cpu->pc);
    if (cpu->pc == 0x8003b160u) {
        uint32_t callback;
        if (!musashi_boot_read32(&boot->memory, 0x8006cbd4u, &callback))
            fputs("native_boot: DMA_REGISTER unreadable\n", stderr);
        else fprintf(stderr, "native_boot: DMA_REGISTER return_pc=%08x channel=4 "
                     "slot=8006cbd4 callback=%08x previous=%08x DPCR=%08x DICR=%08x\n",
                     cpu->pc, callback, cpu->r[2], boot->dma.control, boot->dma.interrupt);
    }
    if (cpu->pc == 0x8005fcf8u) {
        for (i = 0; i < 8; ++i) {
            uint32_t handle, flag;
            const MusashiBiosEventRecord *record = &boot->bios.events.records[i];
            if (!musashi_boot_read32(&boot->memory, 0x80078c3cu + i * 4u, &handle) ||
                !musashi_boot_read32(&boot->memory, 0x80078c5cu + i * 4u, &flag)) {
                fputs("native_boot: EVENT_STATE unreadable\n", stderr);
                return;
            }
            fprintf(stderr, "native_boot: EVENT_STATE index=%u handle=%08x flag=%08x "
                    "class=%08x status=%08x spec=%08x mode=%08x callback=%08x\n",
                    i, handle, flag, record->class_word, record->status,
                    record->spec, record->mode, record->callback);
        }
    }
    if (cpu->pc == 0x80062340u || cpu->pc == 0x80061f38u)
        fprintf(stderr, "native_boot: CARD_STATE at=%08x pad_policy=%d "
                "card_started=%u card_guest_irq=%d\n", (unsigned)cpu->pc,
                (int)boot->irq_policy.pad, (unsigned)boot->card.card_started,
                guest_irq_enabled(boot));
}

static int load_exe(NativeBoot *boot, const char *path) {
    /* Bound reads to the pinned file size; the loader verifies every byte
     * before writing RAM. No retail bytes are included in this executable. */
    const size_t expected_size = 0x65000u;
    uint8_t *exe;
    size_t size;
    int accepted, extra, io_error;
    FILE *file = fopen(path, "rb");
    if (!file)
        return 0;
    exe = malloc(expected_size);
    if (!exe) {
        fclose(file);
        return 0;
    }
    size = fread(exe, 1, expected_size, file);
    extra = fgetc(file);
    io_error = ferror(file);
    fclose(file);
    accepted = !io_error && size == expected_size && extra == EOF &&
        musashi_boot_map_exe(&boot->memory, exe, size);
    free(exe);
    return accepted;
}

static void dump_display_vram(NativeBoot *boot) {
    unsigned x = boot->gpu.display.x, y = boot->gpu.display.y;
    unsigned width = boot->gpu.display.width ? boot->gpu.display.width : 320u;
    unsigned height = boot->gpu.display.height ? boot->gpu.display.height : 240u;
    uint32_t count = width * height;
    uint16_t *pixels;
    uint64_t nonblack = 0;
    FILE *out;
    unsigned i;
    if (width > 1024u || height > 512u || x > 1024u - width || y > 512u - height)
        return;
    pixels = malloc((size_t)count * sizeof(*pixels));
    if (!pixels) return;
    if (!musashi_gpu_psycross_read_vram(&boot->gpu_renderer, x, y, width, height,
                                        pixels, count)) {
        fprintf(stderr, "native_boot: VRAM_DUMP readable=0 x=%u y=%u %ux%u\n",
                x, y, width, height);
        free(pixels);
        return;
    }
    for (i = 0; i < count; ++i)
        if (pixels[i]) ++nonblack;
    out = fopen("native_vram_display.ppm", "wb");
    if (out) {
        fprintf(out, "P6\n%u %u\n255\n", width, height);
        for (i = 0; i < count; ++i) {
            unsigned r = (pixels[i] & 0x1fu) << 3;
            unsigned g = ((pixels[i] >> 5) & 0x1fu) << 3;
            unsigned b = ((pixels[i] >> 10) & 0x1fu) << 3;
            fputc((int)(r | (r >> 5)), out);
            fputc((int)(g | (g >> 5)), out);
            fputc((int)(b | (b >> 5)), out);
        }
        fclose(out);
    }
    fprintf(stderr, "native_boot: VRAM_DUMP path=native_vram_display.ppm "
            "x=%u y=%u %ux%u nonblack=%llu/%u\n",
            x, y, width, height, (unsigned long long)nonblack, count);
    free(pixels);
    {
        uint16_t row[1024];
        uint64_t full_nonblack = 0, full_checked = 0;
        int ok = 1;
        unsigned yy, xx;
        for (yy = 0; yy < 512u && ok; ++yy) {
            ok = musashi_gpu_psycross_read_vram(&boot->gpu_renderer, 0, yy, 1024, 1,
                                                row, 1024);
            if (!ok) break;
            for (xx = 0; xx < 1024u; ++xx) {
                ++full_checked;
                if (row[xx]) ++full_nonblack;
            }
        }
        fprintf(stderr, "native_boot: VRAM_FULL readable=%d nonblack=%llu/%llu\n",
                ok, (unsigned long long)full_nonblack,
                (unsigned long long)full_checked);
    }
}

static void host_window_inspect(SDL_Window *window) {
    int width = 0, height = 0;
    int (*set_focusable)(SDL_Window *, int);
    unsigned (*get_props)(SDL_Window *);
    void *(*get_ptr)(unsigned, const char *, void *);
    long long (*get_num)(unsigned, const char *, long long);
    if (!window) return;
    /* Spectator scanout only. Never grab, never stay-on-top, never re-raise:
     * Xwayland + SDL_PumpEvents was forcing X input focus back every TAP. */
    SDL_GetWindowSize(window, &width, &height);
    if (width != 1280 || height != 960)
        SDL_SetWindowSize(window, 1280, 960);
    SDL_SetWindowAlwaysOnTop(window, SDL_FALSE);
    SDL_SetWindowGrab(window, SDL_FALSE);
    SDL_SetWindowKeyboardGrab(window, SDL_FALSE);
    SDL_SetWindowMouseGrab(window, SDL_FALSE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
    SDL_CaptureMouse(SDL_FALSE);
    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetWindowTitle(window,
                       "Brave Fencer Musashi - native VRAM");
    set_focusable = (int (*)(SDL_Window *, int))dlsym(RTLD_DEFAULT, "SDL_SetWindowFocusable");
    if (set_focusable)
        set_focusable(window, 0);
    get_props = (unsigned (*)(SDL_Window *))dlsym(RTLD_DEFAULT, "SDL_GetWindowProperties");
    get_ptr = (void *(*)(unsigned, const char *, void *))dlsym(RTLD_DEFAULT, "SDL_GetPointerProperty");
    get_num = (long long (*)(unsigned, const char *, long long))dlsym(RTLD_DEFAULT, "SDL_GetNumberProperty");
    if (get_props && get_ptr && get_num) {
        unsigned props = get_props(window);
        void *dpy = get_ptr(props, "SDL.window.x11.display", NULL);
        unsigned long xid = (unsigned long)get_num(props, "SDL.window.x11.window", 0);
        if (dpy && xid)
            musashi_x11_spectator(dpy, xid);
    }
    musashi_x11_spectator_focused();
}

static void hold_window(NativeBoot *boot) {
    const char *env = getenv("MUSASHI_HOLD_WINDOW_MS");
    unsigned ms = env ? (unsigned)strtoul(env, NULL, 10) : 15000u;
    Uint32 start;
    SDL_Window *window = SDL_GL_GetCurrentWindow();
    if (!window || !ms) return;
    host_window_inspect(window);
    if (boot && boot->start_preview_paused)
        SDL_SetWindowTitle(window,"Brave Fencer Musashi - start screen preview (paused)");
    fprintf(stderr, "native_boot: HOLD_WINDOW ms=%u\n", ms);
    start = SDL_GetTicks();
    while (SDL_GetTicks() - start < ms) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) return;
        if (boot)
            (void)musashi_gpu_psycross_present(&boot->gpu_renderer);
        SDL_Delay(16);
    }
}

int main(int argc, char **argv) {
    static NativeBoot boot; /* One stable, zero-initialized owner. */
    MusashiEntryRunStop entry_stop = {0};
    MusashiResetGraphPrefixStop stop = {0};
    MusashiResetGraphPrefixStatus status;
    uint16_t guard, enabled;
    uint32_t slot0, slot3, tick;
    int cleanup_ok = 1;
    int presentation_ok, gpu_removed;
    unsigned event_used = 0, index;

    if (argc != 2 && argc != 4) {
        fputs("usage: musashi_native_boot <pinned SLUS_007.26> [pinned cue pinned bin]\n", stderr);
        return 2;
    }
    boot.exe_path = argv[1];
    if (!load_exe(&boot, argv[1])) {
        fputs("native_boot: pinned retail EXE rejected before startup\n", stderr);
        return 2;
    }
    if (argc == 4) {
        boot.media = musashi_disc_media_open_pinned(argv[2], argv[3]);
        if (!boot.media) {
            fputs("native_boot: pinned media rejected before startup\n", stderr);
            return 2;
        }
    }
    musashi_bios_kernel_init(&boot.bios);
    musashi_sio_controller_init_disconnected(&boot.sio);
    if (!musashi_bios_card_init(&boot.card, &boot.bios) ||
        !musashi_bios_kernel_start_cd(&boot.bios, unavailable_bios_cd, &boot)) {
        native_devices_shutdown(&boot);
        return 2;
    }
    /* The pinned US game uses NTSC. Select the native source policy before
     * PsyCross creates its worker; its otherwise-unset mode selects PAL. */
    SetVideoMode(MODE_NTSC);
    /* Xwayland + BYPASS_COMPOSITOR leaves a mapped GL window the desktop
     * never composites; the 3-hour hold is then invisible. */
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "0");
    SDL_SetHint(SDL_HINT_MOUSE_AUTO_CAPTURE, "0");
    SDL_SetHint(SDL_HINT_ALLOW_ALT_TAB_WHILE_GRABBED, "1");
    SDL_SetHint("SDL_WINDOW_ACTIVATE_WHEN_RAISED", "0");
    SDL_SetHint("SDL_WINDOW_ACTIVATE_WHEN_SHOWN", "0");
    PsyX_Initialise("Brave Fencer Musashi - native VRAM", 1280, 960, 0);
    fprintf(stderr, "native_boot: VIDEO_SOURCE mode=%d policy=NTSC selected_before_worker=1\n",
            GetVideoMode());
    if (!SDL_GL_GetCurrentWindow() || !g_intrMutex) {
        fputs("native_boot: PsyCross display unavailable; startup not observed\n", stderr);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 77;
    }
    host_window_inspect(SDL_GL_GetCurrentWindow());
    /* SDL converts SIGTERM into an event, but source execution may not pump
     * window events while waiting for I/O. Stop at the next clock boundary
     * and retain the diagnostic dump instead of leaving timeout's child alive. */
    signal(SIGTERM,request_host_stop);
    signal(SIGINT,request_host_stop);
    boot.trace_cd_timing = getenv("MUSASHI_NATIVE_CD_TIMING") != NULL;
    if (!musashi_bios_heap_init(&boot.heap,&boot.memory,&boot,epoch_owner)) {
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    boot.heap_device=(MusashiHeapDevice){&boot,init_heap};
    boot.gpu_io=(MusashiGpuIoDevice){&boot,gpu_io_read32,gpu_io_write32};
    if (!musashi_psycross_irq_runtime_init(&boot.irq, &boot.memory, NULL)) {
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    if (!musashi_bios_exception_init_selected(&boot.exception_image,&boot.memory,&boot.bios,boot.irq.cpu_status) ||
        !musashi_psycross_irq_scheduler_bind_context(&boot.irq.scheduler,native_cpu_context,&boot)) {
        fputs("native_boot: CPU/image ownership refused before CRT\n",stderr);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    boot.cpu_transfer=(MusashiCpuTransferDevice){
        .userdata=&boot,.read_status=cpu_read_status,.write_status=cpu_write_status,
        .write_control=cpu_write_control,.write_data=cpu_write_gte_data,.read_data=cpu_read_gte_data,
        .read_control=cpu_read_control,.command=cpu_gte_command
    };
    boot.image_device=(MusashiBiosImageDevice){&boot,musashi_bios_exception_intersects,
        image_read,image_write,image_table,image_publish};
    if (!musashi_gpu_psycross_init(&boot.gpu_renderer, &boot.gpu_backend) ||
        !musashi_gpu_controller_init(&boot.gpu, &boot.gpu_backend)) {
        fputs("native_boot: GPU backend initialization refused\n", stderr);
        if (boot.gpu_renderer.initialized)
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    (void)musashi_gpu_psycross_present(&boot.gpu_renderer);
    if (boot.media) {
        const MusashiCdOwnedHardware hardware = {
            .userdata=&boot, .current_thread=epoch_owner,
            .healthy=cd_hardware_healthy, .raise_irq4=raise_cd_irq,
            .data_transfer_idle=cd_data_transfer_idle
        };
        boot.cd_drive = musashi_cd_owned_open_bios_idle(boot.media, &hardware, 0);
        if (!boot.cd_drive) {
            fputs("native_boot: owned CD initialization refused before CRT\n", stderr);
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
            native_devices_shutdown(&boot);
            PsyX_Shutdown();
            return 2;
        }
        boot.cd_registers = (MusashiCdRegisterDevice){.userdata=&boot,.read8=cd_read8,.write8=cd_write8};
        boot.audio = musashi_audio_sdl_create();
        boot.spu = musashi_spu_cd_audio_create();
        if (!boot.audio || !boot.spu || !musashi_audio_sdl_open(boot.audio) ||
            !musashi_spu_cd_audio_init_bios_muted(boot.spu,
                musashi_audio_sdl_backend(boot.audio), 0)) {
            fputs("native_boot: real audio owner unavailable before CRT; startup NOT_RUN\n", stderr);
            native_devices_shutdown(&boot);
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
            PsyX_Shutdown();
            return 77;
        }
        if (!musashi_cd_owned_set_xa_sink(boot.cd_drive,submit_xa_pcm,&boot)) {
            native_devices_shutdown(&boot);PsyX_Shutdown();return 2;
        }
        boot.cd_spu = (MusashiCdSpuDevice){&boot, spu_read16, spu_write16};
    }
    {
        const MusashiSioPadDevice pad = {&boot, epoch_owner, sample_keyboard_pad, raise_sio_irq};
        if (!musashi_sio_controller_bind_digital_pad(&boot.sio, &pad)) {
            fputs("native_boot: fresh digital pad binding refused\n", stderr);
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
            native_devices_shutdown(&boot);
            PsyX_Shutdown();
            return 2;
        }
    }
    musashi_irq_policy_init(&boot.irq_policy);
    boot.card_device = (MusashiBiosCardStartDevice){
        .userdata = &boot,
        .write_sio16 = card_write_sio16,
        .read_irq32 = card_read_irq32,
        .write_irq32 = card_write_irq32,
        .enter_critical = card_enter_critical,
        .exit_critical = card_exit_critical,
        .exchange_pad = exchange_clear_pad,
        .change_timer = change_clear_timer,
        .read_pad = card_read_pad,
        .read_sio16 = card_read_sio16,
        .read_sio8 = card_read_sio8,
        .write_sio8 = card_write_sio8,
        .cards_disconnected = cards_disconnected,
        .execute_event = execute_event,
    };
    if (!musashi_bios_card_bind_start_device(&boot.card, &boot.card_device)) {
        fputs("native_boot: card device binding refused\n", stderr);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    if (!musashi_bios_backup_unit_init(&boot.backup_unit, &boot.bios, &boot.card)) {
        fputs("native_boot: backup-unit ownership refused\n", stderr);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    boot.irq.scheduler.raise_vblank = raise_vblank;
    boot.irq.scheduler.raise_userdata = &boot;
    boot.irq.scheduler.before_dispatch = before_irq_dispatch;
    boot.irq.scheduler.before_dispatch_userdata = &boot;
    boot.registration.userdata = &boot;
    boot.registration.read16 = registration_read16;
    boot.registration.write16 = registration_write16;
    boot.registration.b0_5b = change_clear_pad;
    boot.registration.c0_0a = change_clear_timer;
    musashi_dma_controller_init(&boot.dma, &boot.irq.controller);
    musashi_mdec_init(&boot.mdec, &boot.memory, &boot.dma);
    boot.dma_irq.userdata = &boot;
    boot.dma_irq.read32 = dma_irq_read32;
    boot.dma_irq.write32 = dma_irq_write32;
    if (!musashi_psycross_irq_runtime_bind_dma(&boot.irq, &boot.dma_irq)) {
        fputs("native_boot: DMA interrupt owner binding refused before CRT\n", stderr);
        native_devices_shutdown(&boot);
        musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
        PsyX_Shutdown();
        return 2;
    }
    {
        const MusashiGpuDma2Device device={&boot,epoch_owner,gpu_dma_healthy};
        boot.gpu_dma=musashi_gpu_dma2_open(&boot.memory,&boot.dma,&boot.gpu,&device,0);
        if (!boot.gpu_dma) {
            fputs("native_boot: GPU DMA2 owner initialization refused before CRT\n",stderr);
            native_devices_shutdown(&boot);
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
            PsyX_Shutdown();
            return 2;
        }
        {
            const MusashiDmaOtcDevice otc_device={&boot,epoch_owner,gpu_dma_healthy};
            boot.dma_otc=musashi_dma_otc_open(&boot.memory,&boot.dma,&otc_device,0);
            if (!boot.dma_otc) {
                fputs("native_boot: DMA6 OTC owner initialization refused before CRT\n",stderr);
                native_devices_shutdown(&boot);
                musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
                PsyX_Shutdown();
                return 2;
            }
        }
    }
    if (boot.cd_drive) {
        const MusashiCdDma3Device device = {.userdata=&boot,.current_thread=epoch_owner,
            .healthy=cd_dma_healthy,.read_data=cd_dma_read_data,.data_available=cd_dma_available,.request_asserted=cd_dma_request};
        boot.cd_dma=musashi_cd_dma3_open(&boot.memory,&boot.dma,&device,0);
        if (!boot.cd_dma) {
            fputs("native_boot: CD DMA3 owner initialization refused before CRT\n",stderr);
            native_devices_shutdown(&boot);
            musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
            PsyX_Shutdown();
            return 2;
        }
        boot.cd_registers.read32=cd_read32;
        boot.cd_registers.write32=cd_write32;
    }
    boot.callback.userdata = &boot;
    boot.callback.read16 = irq_read16;
    boot.callback.write16 = irq_write16;
    boot.callback.write32 = control_write32;
    boot.callback.registration_device = &boot.registration;
    boot.callback.hook_entry_int = musashi_psycross_irq_scheduler_hook_entry_int;
    boot.callback.hook_entry_int_userdata = &boot.irq.scheduler;
    boot.callback.a0_72 = remove_bios_cd;
    boot.callback.exit_critical_section = exit_critical;
    boot.callback.checkpoint = checkpoint;
    boot.gpu_device.userdata = &boot;
    boot.gpu_device.read32 = gpu_read32;
    boot.gpu_device.write32 = gpu_write32;
    boot.gpu_device.read16 = irq_read16;
    boot.gpu_device.write16 = irq_write16;
    boot.callback.gpu_cw = gpu_cw;
    boot.callback.reset_device = &boot.gpu_device;
    boot.cd.userdata = &boot;
    boot.cd.enter_critical_result = enter_critical_result;
    boot.cd.b0_5b = exchange_clear_pad;
    boot.cd.b0_4a = init_card;
    boot.cd.b0_4b = start_card;
    boot.cd.a0_70 = init_backup_unit;
    boot.event.userdata = &boot;
    boot.event.open_event = open_event;
    boot.event.enable_event = enable_event;
    boot.event.b0_0b = test_event;
    boot.input.userdata = &boot;
    boot.input.dequeue_irq_result = input_dequeue;
    boot.input.enqueue_irq_result = input_enqueue;
    boot.input.change_timer_result = input_change_timer;
    boot.input.read32 = card_read_irq32;
    boot.input.write32 = input_write32;
    boot.input.read16 = input_read16;
    boot.input.write16 = input_write16;
    boot.input.read8 = card_read_sio8;
    boot.input.write8 = input_write8;
    musashi_source_clock_init(&boot.source_clock);
    /* Fresh native BIOS Timer2 policy, not the retail capture's elapsed
     * counter or absolute cycle phase. Mounted CD uses this same epoch. */
    musashi_timer2_init(&boot.timer2, 0);
    if (!musashi_scanline_timer_init_paced(&boot.timer1, 0)) {
        native_devices_shutdown(&boot);
        musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
        PsyX_Shutdown();
        return 2;
    }
    boot.execution_clock.userdata = &boot;
    boot.execution_clock.advance = advance_source_clock;
    boot.cd_services = (MusashiCdIrqServices){.userdata=&boot,
        .deliver_event=deliver_cd_event,.callback_device=&boot.callback,
        .gpu_io=&boot.gpu_io, .dma=&boot.dma_irq,
        .cd_spu=boot.spu ? &boot.cd_spu : NULL,
        .event=&boot.event};
    if (boot.cd_drive && (!musashi_psycross_irq_runtime_bind_cd(
            &boot.irq, &boot.cd_registers, &boot.execution_clock) ||
        !musashi_psycross_irq_runtime_bind_cd_services(&boot.irq, &boot.cd_services))) {
        fputs("native_boot: CD interrupt owner binding refused before CRT\n", stderr);
        native_devices_shutdown(&boot);
        musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
        PsyX_Shutdown();
        return 2;
    }
    boot.input.clock = &boot.execution_clock;
    boot.bios_input_device.userdata = &boot;
    boot.bios_input_device.execute = input_execute;
    musashi_boot_bios_callback_frame_init(&boot.bios_callback_frame);
    if (!musashi_bios_input_init(&boot.bios_input, &boot.memory, &boot.bios,
                                &boot.card, &boot.bios_input_device)) {
        fputs("native_boot: input ownership initialization refused\n", stderr);
        native_devices_shutdown(&boot);
        PsyX_Shutdown();
        return 2;
    }
    {
        const MusashiDeviceEpochAdapter adapter = {&boot, epoch_owner, epoch_collect,
            epoch_wait, epoch_advance_devices, epoch_video_edge};
        if (!musashi_device_epoch_init(&boot.epoch, &adapter)) {
            fputs("native_boot: fresh device epoch refused before CRT\n", stderr);
            native_devices_shutdown(&boot);
            PsyX_Shutdown();
            return 2;
        }
    }
    /* The source thread queues edges only. The live CPU's checkpoints pump
     * device/guest work synchronously on this thread. No broad interrupt
     * mutex is held, and SYS2 only changes guest IRQ eligibility. Timer1
     * follows the selected NTSC source rate after its first real VBlank. */
    /* The mapped image enters its actual CRT. Native register policy is zero
     * initially, including no BIOS return target; no retail snapshot seed.
     * One CPU and checkpoint identity survives every supported call/return. */
    boot.startup_devices = (MusashiStartupPrefixDevice){
        .callback=&boot.callback, .cd=&boot.cd, .event=&boot.event,
        .input=&boot.input, .clock=&boot.execution_clock,
        .cd_registers=boot.cd_drive ? &boot.cd_registers : NULL,
        .cd_spu=boot.spu ? &boot.cd_spu : NULL, .heap=&boot.heap_device,
        .gpu_io=&boot.gpu_io, .cpu_transfer=&boot.cpu_transfer, .bios_image=&boot.image_device
    };
    if (!musashi_psycross_irq_runtime_bind_source_execute(&boot.irq,
            source_irq_execute, &boot)) {
        fputs("native_boot: source IRQ execute binding refused before CRT\n", stderr);
        native_devices_shutdown(&boot);
        musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
        PsyX_Shutdown();
        return 2;
    }
    status = musashi_boot_run_entry_with_devices(&boot.memory, 0, &boot.startup_devices,
        console_bytes, NULL, observe_entry, &boot, &entry_stop);
    {
        MusashiCpuStatusSnapshot state;
        MusashiGteSnapshot gte;
        int cpu_valid=musashi_cpu_status_snapshot(boot.irq.cpu_status,&state);
        int gte_valid=musashi_gte_owner_snapshot(&boot.gte,&gte);
        fprintf(stderr,"native_boot: CPU_OWNER valid=%d sr=%08x sequence=%llu active=%d "
                "kernel_entered=%d faulted=%d host_depth=%u\n",cpu_valid,cpu_valid ? state.sr : 0,
                cpu_valid ? (unsigned long long)state.sequence : 0,cpu_valid ? state.active : -1,
                cpu_valid ? state.kernel_entered : -1,cpu_valid ? state.faulted : -1,boot.host_service_depth);
        fprintf(stderr,"native_boot: BIOS_IMAGE generation=%llu variant=%u writes=%llu entries=%llu "
                "dirty=%d faulted=%d required=%d bound=%d card_hook=%d\n",
                (unsigned long long)boot.exception_image.generation,(unsigned)boot.exception_image.variant,
                (unsigned long long)boot.exception_image.writes,(unsigned long long)boot.exception_image.entries,
                boot.exception_image.dirty,boot.exception_image.faulted,boot.bios.exception_required,
                boot.bios.exception_binding==&boot.exception_image.binding,boot.bios.early_hook==&boot.card.early_hook);
        fprintf(stderr,"native_boot: GTE_OWNER valid=%d initialized=%d faulted=%d writes=%llu controls=",
                gte_valid,gte_valid ? gte.initialized : 0,gte_valid ? gte.faulted : -1,
                gte_valid ? (unsigned long long)gte.write_count : 0);
        if (gte_valid) for (unsigned i=0;i<32;i++) fprintf(stderr,"%s%08x",i ? "," : "",gte.control[i]);
        fputc('\n',stderr);
        fprintf(stderr,"native_boot: GTE_DATA_OWNER valid=%d writes=%llu reads=%llu data=",
                gte_valid,gte_valid ? (unsigned long long)gte.data_write_count : 0,
                gte_valid ? (unsigned long long)gte.data_read_count : 0);
        if (gte_valid) for (unsigned i=0;i<32;i++) fprintf(stderr,"%s%08x",i ? "," : "",gte.data[i]);
        fputc('\n',stderr);
        if (!cpu_valid || !gte_valid) cleanup_ok=0;
    }
    stop = entry_stop.boundary;
    fprintf(stderr,"native_boot: EXECUTION_BOUNDARY reason=%s\n",
            host_stop_signal ? "HOST_STOP" :
            status==MUSASHI_RESETGRAPH_PREFIX_STEP_LIMIT ? "STEP_LIMIT" :
            status==MUSASHI_RESETGRAPH_PREFIX_COMPLETE ? "RETURNED" :
            status==MUSASHI_RESETGRAPH_PREFIX_UNSUPPORTED_CALL ? "UNBOUND_CALL" : "REFUSED");
    fprintf(stderr,"native_boot: MDEC_SETUP command=%08x remaining=%u transfers=%llu "
            "control=%08x dma0=%08x dma1=%08x\n",boot.mdec.command,
            boot.mdec.remaining,(unsigned long long)boot.mdec.transfers,
            boot.mdec.control,boot.mdec.chcr[0],boot.mdec.chcr[1]);
    fprintf(stderr, "native_boot: CPU_BOUNDARY pc=%08x npc=%08x v0=%08x v1=%08x "
            "a0=%08x a1=%08x s0=%08x t1=%08x t2=%08x sp=%08x ra=%08x\n",
            entry_stop.cpu.pc, entry_stop.cpu.npc, entry_stop.cpu.r[2], entry_stop.cpu.r[3],
            entry_stop.cpu.r[4], entry_stop.cpu.r[5], entry_stop.cpu.r[16],
            entry_stop.cpu.r[9], entry_stop.cpu.r[10], entry_stop.cpu.r[29],
            entry_stop.cpu.r[31]);
    {
        uint32_t overlay=0x800cedfcu, i, word=0, index=0;
        fputs("native_boot: OVERLAY_WORDS", stderr);
        for (i=0;i<8u;++i) {
            musashi_boot_read32(&boot.memory, overlay+i*4u, &word);
            fprintf(stderr," %08x", word);
        }
        fputc('\n', stderr);
        musashi_boot_read32(&boot.memory, 0x800c99e4u, &index);
        fprintf(stderr,"native_boot: OVERLAY_INDEX %08x table", index & 0xffffu);
        for (i=0;i<8u;++i) {
            musashi_boot_read32(&boot.memory, 0x800cf450u+i*4u, &word);
            fprintf(stderr," %08x", word);
        }
        fputc('\n', stderr);
    }
    {
        /* Opt-in capture of the guest's own 2 MiB main RAM at the stop. A
         * member's loaded code must be compared against this image rather than
         * against another member's extracted blob. */
        const char *ram_path = getenv("MUSASHI_DUMP_RAM");
        if (ram_path && ram_path[0]) {
            uint8_t *ram = musashi_boot_ram_span(&boot.memory, 0x80000000u, MUSASHI_RAM_SIZE);
            FILE *out = ram ? fopen(ram_path, "wb") : NULL;
            if (!out) {
                fprintf(stderr, "native_boot: RAM_DUMP refused path=%s\n", ram_path);
            } else {
                size_t written = fwrite(ram, 1u, MUSASHI_RAM_SIZE, out);
                fclose(out);
                fprintf(stderr, "native_boot: RAM_DUMP path=%s base=80000000 bytes=%u written=%u\n",
                        ram_path, (unsigned)MUSASHI_RAM_SIZE, (unsigned)written);
            }
        }
    }
    {
        /* Boot-progress diagnostic: the 80044DBC initializer's first store
         * targets the live v1 pointer loaded from [0x8006CF4C]. */
        uint32_t initializer_pointer = 0;
        musashi_boot_read32(&boot.memory, 0x8006cf4cu, &initializer_pointer);
        fprintf(stderr, "native_boot: CD_INIT_POINTER v1=%08x cf4c=%08x\n",
                entry_stop.cpu.r[3], initializer_pointer);
    }
    fprintf(stderr, "native_boot: SOURCE_CLOCK cycles=%llu faulted=%d "
            "scope=%s devices_advanced=DEVICE_EPOCH\n",
            (unsigned long long)boot.source_clock.cycles, boot.source_clock.faulted,
            boot.cd_drive ? "STARTUP_INPUT_CD_IRQ_SOURCE_ONLY" : "STARTUP_AND_INPUT_SOURCE_ONLY");
    fprintf(stderr, "native_boot: DEVICE_EPOCH cycles=%llu source_edges=%llu cuts=%llu "
            "waits=%llu frequency=%llu faulted=%d profile=PACED_HOST_TIME cd_advanced=%d\n",
            (unsigned long long)boot.epoch.cycle, (unsigned long long)boot.epoch.last_sequence,
            (unsigned long long)boot.epoch.cuts, (unsigned long long)boot.epoch.waits,
            (unsigned long long)boot.epoch.frequency, boot.epoch.faulted,
            boot.cd_drive != NULL);
    if (boot.cd_drive) {
        MusashiCdOwnedState cd_state;
        if (!musashi_cd_owned_get_state(boot.cd_drive, &cd_state)) cleanup_ok = 0;
        else fprintf(stderr, "native_boot: CD_OWNER cycle=%llu due=%llu command=%02x "
                     "phase=%u if=%02x enable=%02x fifo=%u fault=%u irq_requests=%llu "
                     "common_delay_written=%d common_delay=%08x\n",
                     (unsigned long long)cd_state.cycle, (unsigned long long)cd_state.due,
                     cd_state.command, cd_state.phase, cd_state.interrupt, cd_state.enable,
                     cd_state.response_count, cd_state.fault,
                     (unsigned long long)boot.cd_irq_requests,
                     boot.common_delay_written, boot.common_delay);
        fprintf(stderr, "native_boot: CD_IRQ frame_busy=%d frame_faulted=%d "
                "instructions=%u call=%08x target=%08x\n",
                boot.irq.cd_frame.busy, boot.irq.cd_frame.faulted,
                boot.irq.cd_frame.instructions, boot.irq.cd_stop.call_address,
                boot.irq.cd_stop.target_address);
        fprintf(stderr,"native_boot: CD_IRQ_BUDGET exhausted=%u\n",
                boot.irq.cd_frame.budget_exhausted);
        {
            uint32_t mode=0, slot=0, p0=0, p1=0, p2=0, p3=0, p4=0, p5=0, kind_word=0;
            uint8_t kind=0;
            musashi_boot_read32(&boot.memory, 0x800ae6f8u, &mode);
            musashi_boot_read32(&boot.memory, 0x8006cc88u, &slot);
            musashi_boot_read32(&boot.memory, 0x8006cf64u, &kind_word);
            kind = (uint8_t)((kind_word >> 8) & 0xffu);
            musashi_boot_read32(&boot.memory, 0x8006cf5cu, &p0);
            musashi_boot_read32(&boot.memory, 0x8006cf80u, &p1);
            musashi_boot_read32(&boot.memory, 0x8006cf84u, &p2);
            musashi_boot_read32(&boot.memory, 0x8006cf88u, &p3);
            musashi_boot_read32(&boot.memory, 0x8006cf8cu, &p4);
            musashi_boot_read32(&boot.memory, 0x8006cf90u, &p5);
            fprintf(stderr,
                    "native_boot: CD_IRQ_RAM mode=%08x slot=%08x kind=%02x "
                    "ptr=%08x,%08x,%08x,%08x,%08x,%08x\n",
                    mode, slot, kind, p0, p1, p2, p3, p4, p5);
        }
        if (musashi_cd_owned_get_state(boot.cd_drive,&cd_state))
            fprintf(stderr,"native_boot: CD_DATA reading=%u next_lba=%u sector_due=%llu "
                "fetched=%llu published=%llu requested=%u valid=%u fifo_lba=%u size=%u cursor=%u bytes=%llu\n",
                cd_state.reading,cd_state.next_lba,(unsigned long long)cd_state.sector_due,
                (unsigned long long)cd_state.sectors_fetched,(unsigned long long)cd_state.sectors_published,
                cd_state.data_requested,cd_state.fifo_valid,cd_state.fifo_lba,cd_state.fifo_size,
                cd_state.fifo_cursor,(unsigned long long)cd_state.data_bytes_read);
        else cleanup_ok=0;
        fprintf(stderr,"native_boot: CD_SEEK seeking=%u target=%u position_valid=%u position=%u starts=%llu completions=%llu media_reads=%llu retirements=%llu\n",
                cd_state.seeking,cd_state.seek_target_lba,cd_state.position_valid,cd_state.position_lba,
                (unsigned long long)cd_state.seek_starts,(unsigned long long)cd_state.seek_completions,
                (unsigned long long)cd_state.seek_sector_reads,(unsigned long long)cd_state.buffer_retirements);
        fprintf(stderr,"native_boot: CD_ANNOUNCED valid=%u claimed=%u lba=%u sequence=%llu requested_sequence=%llu fifo_latches=%llu\n",
                cd_state.announced_valid,cd_state.announced_claimed,cd_state.announced_lba,
                (unsigned long long)cd_state.announced_sequence,(unsigned long long)cd_state.requested_sequence,
                (unsigned long long)cd_state.fifo_latches);
        if (boot.cd_dma) {
            MusashiCdDma3State dma;
            if (!musashi_cd_dma3_get_state(boot.cd_dma,&dma)) cleanup_ok=0;
            else fprintf(stderr,"native_boot: CD_DMA3 cycle=%llu due=%llu madr=%08x bcr=%08x "
                "chcr=%08x delay=%08x transfers=%llu bytes=%llu fault=%u\n",
                (unsigned long long)dma.cycle,(unsigned long long)dma.due,dma.madr,dma.bcr,
                dma.chcr,dma.cdrom_delay,(unsigned long long)dma.transfers,
                (unsigned long long)dma.bytes,dma.fault);
        }
    }
    if (boot.spu) {
        MusashiSpuCdAudioSnapshot audio_state;
        if (!musashi_spu_cd_audio_snapshot(boot.spu, &audio_state)) cleanup_ok = 0;
        else fprintf(stderr, "native_boot: SPU_OWNER cycle=%llu samples=%llu "
                     "main_left=%04x main_right=%04x cd_left=%04x cd_right=%04x "
                     "control=%04x submitted=%zu queued=%zu faulted=%d "
                     "profile=SETTLED_BIOS_MAIN_MUTE audible_game=NOT_OBSERVED\n",
                     (unsigned long long)audio_state.cycle,
                     (unsigned long long)audio_state.sample_index,
                     (unsigned)(uint16_t)audio_state.main_left_current,
                     (unsigned)(uint16_t)audio_state.main_right_current,
                     (unsigned)(uint16_t)audio_state.cd_left_gain,
                     (unsigned)(uint16_t)audio_state.cd_right_gain,
                     audio_state.control, audio_state.submitted_frames,
                     audio_state.queued_frames, audio_state.faulted);
    }
    fprintf(stderr, "native_boot: TIMER2 count=%04x mode=%04x target=%04x epoch=0 "
            "profile=PACED_EVENT_SERVICED irq_enabled=0\n",
            boot.timer2.count, boot.timer2.mode, boot.timer2.target);
    fprintf(stderr, "native_boot: VIDEO_TIMING timer1_cycle=%llu count=%04x "
            "subcycle=%u running=%d faulted=%d profile=NTSC_2146_EVENT_SERVICED "
            "gpu_parity=%u gpu_reset_sequence=%llu\n",
            (unsigned long long)boot.timer1.last_cycles, boot.timer1.count,
            boot.timer1.subcycle, boot.timer1.running, boot.timer1.faulted,
            boot.gpu.vblank_parity, (unsigned long long)boot.gpu_reset_sequence);
    {
        uint32_t busy=0, saved_mask=0, history[3]={0};
        int valid=musashi_boot_read32(&boot.memory,0x80072790u,&busy) &&
            musashi_boot_read32(&boot.memory,0x80072894u,&saved_mask) &&
            musashi_boot_read32(&boot.memory,0x8007287cu,&history[0]) &&
            musashi_boot_read32(&boot.memory,0x80072880u,&history[1]) &&
            musashi_boot_read32(&boot.memory,0x80072884u,&history[2]);
        fprintf(stderr,"native_boot: DRAW_OWNER dma_direction=%u chcr=%08x "
                "display_disabled=%d gpu_faulted=%d queue_valid=%d busy=%08x "
                "saved_mask=%08x history=%08x,%08x,%08x\n",
                boot.gpu.dma_direction,boot.dma.gpu_channel_control,
                boot.gpu.display_disabled,boot.gpu.faulted,valid,busy,saved_mask,
                history[0],history[1],history[2]);
    }
    fprintf(stderr, "native_boot: SIO profile=DIGITAL_PORT1_CARDS_ABSENT bound=%d "
            "cycle=%llu transmitted=%llu keyboard_polls=%llu ack_pending=%d faulted=%d\n",
            boot.sio.pad_bound, (unsigned long long)boot.sio.cycle,
            (unsigned long long)boot.sio.transmitted_bytes,
            (unsigned long long)boot.keyboard_polls, boot.sio.ack_pending, boot.sio.faulted);
    observe_input_state(&boot, entry_stop.cpu.pc);
    if (!musashi_boot_read16(&boot.memory, 0x8006bafcu, &guard) ||
        !musashi_boot_read16(&boot.memory, 0x8006bb2cu, &enabled) ||
        !musashi_boot_read32(&boot.memory, 0x8006bb00u, &slot0) ||
        !musashi_boot_read32(&boot.memory, 0x8006bb0cu, &slot3) ||
        !musashi_boot_read32(&boot.memory, 0x8006cbb8u, &tick)) {
        fputs("native_boot: startup state unreadable\n", stderr);
        exit(2);
    }
    for (index = 0; index < MUSASHI_BIOS_EVENTS_CAPACITY; index++)
        if (boot.bios.events.records[index].status) event_used++;
    /* A returned bounded prefix is still a stop. Unhook before releasing
     * source registration and this owner's lifetime. */
    fprintf(stderr,
        "native_boot: STOP status=%d pc=%08x target=%08x IRQ_installed=%d "
        "I_STAT=%04x I_MASK=%04x DPCR=%08x DICR=%08x TIMER1_MODE=%04x "
        "custom_vblank=%d deliveries=%u failed_target=%08x\n",
        (int)status, (unsigned)stop.call_address, (unsigned)stop.target_address,
        boot.irq.scheduler.installed, (unsigned)boot.irq.controller.status,
        (unsigned)boot.irq.controller.mask, (unsigned)boot.dma.control,
        (unsigned)boot.dma.interrupt, (unsigned)boot.timer1.mode,
        musashi_irq_policy_custom_vblank(&boot.irq_policy),
        (unsigned)boot.irq.scheduler.deliveries,
        (unsigned)boot.irq.failed_target);
    fprintf(stderr, "native_boot: guest guard=%04x enabled=%04x slot0=%08x "
            "slot3=%08x tick=%08x\n", (unsigned)guard, (unsigned)enabled,
            (unsigned)slot0, (unsigned)slot3, (unsigned)tick);
    {
        uint32_t dma_slot4 = 0, vblank_slots[8];
        unsigned slot;
        (void)musashi_boot_read32(&boot.memory, 0x8006cbc4u + 16u, &dma_slot4);
        fprintf(stderr, "native_boot: dma_slot4=%08x dma_bound=%d\n",
                (unsigned)dma_slot4, boot.irq.dma_device != NULL);
        fputs("native_boot: vblank_slots", stderr);
        for (slot = 0; slot < 8; ++slot) {
            vblank_slots[slot] = 0;
            (void)musashi_boot_read32(&boot.memory, 0x8006cb98u + slot * 4u,
                                      &vblank_slots[slot]);
            fprintf(stderr, " %u=%08x", slot, (unsigned)vblank_slots[slot]);
        }
        fputc('\n', stderr);
    }
    fprintf(stderr, "native_boot: bios_cd_installed=%d bios_event_used=%u "
            "guest_irq_enabled=%d irq_faulted=%d\n", boot.bios.cd_installed,
            event_used, guest_irq_enabled(&boot), boot.irq.scheduler.faulted);
    {
        int scheduler_removed = !boot.irq.scheduler.installed ||
            musashi_psycross_irq_scheduler_uninstall(&boot.irq.scheduler);
        cleanup_ok = scheduler_removed && cleanup_ok;
        fprintf(stderr, "native_boot: scheduler_removed=%d\n", scheduler_removed);
        if (!scheduler_removed) {
            fputs("native_boot: teardown refused while source registration remains live\n",stderr);
            return 2;
        }
    }
    fprintf(stderr, "native_boot: card_initialized=%u card_active=%u card_pad_started=%d "
            "card_hook_installed=%d card_hook_calls=%llu\n", (unsigned)boot.card.initialized_word,
            (unsigned)boot.card.fast_track_active, (int)boot.card.pad_started,
            boot.bios.early_hook == &boot.card.early_hook,
            (unsigned long long)boot.card.hook_calls);
    fprintf(stderr, "native_boot: card_started=%u card_sio_installed=%d "
            "card_port=%u card_vblank_calls=%llu card_maintenance_calls=%llu "
            "card_delay_calls=%u SIO_MODE=%04x SIO_BAUD=%04x SIO_CONTROL=%04x\n",
            (unsigned)boot.card.card_started, boot.card.sio_node.owner == &boot.bios,
            (unsigned)boot.card.port, (unsigned long long)boot.card.vblank_calls,
            (unsigned long long)boot.card.maintenance_calls, (unsigned)boot.card.delay_calls,
            (unsigned)boot.sio.mode, (unsigned)boot.sio.baud, (unsigned)boot.sio.control);
    {
        unsigned directory_zero = 0, broken_ff = 0, statuses_zero = 0;
        unsigned p, e, b;
        for (p = 0; p < 2; ++p) {
            for (e = 0; e < 15; ++e)
                for (b = 0; b < 32; ++b)
                    directory_zero += boot.backup_unit.directory[p][e][b] == 0;
            for (e = 0; e < 20; ++e)
                broken_ff += boot.backup_unit.broken[p][e] == UINT32_MAX;
        }
        for (e = 0; e < 5; ++e) statuses_zero += boot.backup_unit.status[e] == 0;
        fprintf(stderr, "native_boot: bu_stage=%u bu_directory_zero=%u bu_broken_ff=%u "
                "bu_status_zero=%u card_flags=%02x%02x card_action=%u card_last_port=%u "
                "card_operation_step=%u card_irq_installed=%d sio_tx_bytes=%llu\n",
                (unsigned)boot.backup_unit.stage, directory_zero, broken_ff, statuses_zero,
                (unsigned)boot.card.flags[0], (unsigned)boot.card.flags[1],
                (unsigned)boot.card.action_in_progress, (unsigned)boot.card.last_port,
                (unsigned)boot.card.operation_step, boot.card.card_node.owner == &boot.bios,
                (unsigned long long)boot.sio.transmitted_bytes);
    }
    {
        int input_removed = musashi_bios_input_shutdown(&boot.bios_input);
        int bu_removed = musashi_bios_backup_unit_shutdown(&boot.backup_unit);
        int card_removed = musashi_bios_card_shutdown(&boot.card);
        if (!bu_removed && card_removed)
            bu_removed = musashi_bios_backup_unit_shutdown(&boot.backup_unit);
        fprintf(stderr, "native_boot: card_removed=%d bu_removed=%d\n", card_removed, bu_removed);
        fprintf(stderr, "native_boot: input_removed=%d\n", input_removed);
        if (!input_removed || !card_removed || !bu_removed) cleanup_ok = 0;
    }
    {
        uint32_t status_word=0, read_word=0;
        static const uint32_t camera_addresses[]={0x80126950u,0x80126984u,0x80126988u,
            0x8012698cu,0x80126990u,0x80126994u,0x80126998u,0x8012699cu,0x801269a0u};
        for (unsigned c=0;c<sizeof(camera_addresses)/sizeof(camera_addresses[0]);++c) {
            uint32_t value=0;
            int readable=musashi_boot_read32(&boot.memory,camera_addresses[c],&value);
            fprintf(stderr,"native_boot: CAMERA_RAM address=%08x valid=%d value=%08x\n",
                    camera_addresses[c],readable,value);
        }
        static const uint32_t env_addresses[4]={0x800af668u,0x800af6c4u,0x800af77cu,0x800af790u};
        for (unsigned e=0;e<4;++e) {
            unsigned length=e<2 ? 0x5cu : 0x14u;
            const uint8_t *bytes=musashi_boot_ram_span(&boot.memory,env_addresses[e],length);
            fprintf(stderr,"native_boot: FRAMEBUFFER_ENV address=%08x length=%u valid=%d bytes=",
                    env_addresses[e],length,bytes!=NULL);
            if (bytes) for (unsigned i=0;i<length;++i) fprintf(stderr,"%02x",bytes[i]);
            fputc('\n',stderr);
        }
        int valid=musashi_gpu_controller_read32(&boot.gpu,0x1f801814u,&status_word) &&
            musashi_gpu_controller_read32(&boot.gpu,0x1f801810u,&read_word);
        fprintf(stderr,"native_boot: GPUSTAT=%08x GPUREAD=%08x DMA2_CHCR=%08x valid=%d\n",
                status_word,read_word,boot.dma.gpu_channel_control,valid);
        {
            const MusashiGpuDisplayState *states[2]={&boot.gpu.display,&boot.gpu_renderer.display};
            for (unsigned j=0;j<2;++j) {
                const MusashiGpuDisplayState *d=states[j];
                fprintf(stderr,"native_boot: GPU_DISPLAY owner=%s origin=%08x horizontal=%08x "
                        "vertical=%08x mode=%08x x=%u y=%u width=%u height=%u "
                        "h_start=%u h_end=%u v_start=%u v_end=%u divisor=%u disabled=%d\n",
                        j ? "BACKEND" : "CONTROLLER",d->origin,d->horizontal,d->vertical,d->mode,
                        d->x,d->y,d->width,d->height,d->h_start,d->h_end,d->v_start,d->v_end,
                        d->dot_divisor,j ? !boot.gpu_renderer.display_enabled : boot.gpu.display_disabled);
            }
            for (unsigned opcode=5;opcode<=8;++opcode) {
                const uint8_t *byte=musashi_boot_ram_span(&boot.memory,0x80078874u+opcode,1);
                fprintf(stderr,"native_boot: DISPLAY_REGISTER_CACHE opcode=%02x address=%08x "
                        "valid=%d value=%02x\n",opcode,0x80078874u+opcode,byte!=NULL,byte ? *byte : 0);
            }
        }
        fprintf(stderr,"native_boot: GPU_ENV window=%08x area_start=%08x area_end=%08x "
                "offset=%08x mask=%u gp0_accepted=%llu faulted=%d\n",
                boot.gpu.texture_window,boot.gpu.drawing_area_start,boot.gpu.drawing_area_end,
                boot.gpu.drawing_offset,boot.gpu.mask_flags,
                (unsigned long long)boot.gpu.accepted_gp0_words,boot.gpu.faulted);
        fprintf(stderr,"native_boot: GPU_STORE phase=%u remaining=%u pixels=%llu "
                "xy=%u,%u wh=%u,%u px=%u,%u cmd=%08x packet_xy=%08x packet_wh=%08x\n",
                boot.gpu.store_phase,boot.gpu.store_remaining,
                (unsigned long long)boot.gpu.stored_pixels,
                boot.gpu.store_x,boot.gpu.store_y,boot.gpu.store_w,boot.gpu.store_h,
                boot.gpu.store_px,boot.gpu.store_py,boot.gpu.store_command,
                boot.gpu.store_xy,boot.gpu.store_wh);
        {
            uint32_t rect0=0, rect1=0, live0=0, live1=0;
            musashi_boot_read32(&boot.memory, 0x800c5bdcu, &rect0);
            musashi_boot_read32(&boot.memory, 0x800c5be0u, &rect1);
            musashi_boot_read32(&boot.memory, 0x800c5dbcu, &live0);
            musashi_boot_read32(&boot.memory, 0x800c5dc0u, &live1);
            fprintf(stderr,"native_boot: LOADIMAGE_RECT hist=%08x,%08x live=%08x,%08x\n",
                    rect0, rect1, live0, live1);
        }
        fprintf(stderr,"native_boot: GPU_ENV_BACKEND window=%08x area_start=%08x "
                "area_end=%08x offset=%08x mask=%u corners=%d,%d,%d,%d faulted=%d\n",
                boot.gpu_renderer.texture_window,boot.gpu_renderer.drawing_area_start,
                boot.gpu_renderer.drawing_area_end,boot.gpu_renderer.drawing_offset,
                boot.gpu_renderer.mask_flags,boot.gpu_renderer.clip_x1,boot.gpu_renderer.clip_y1,
                boot.gpu_renderer.clip_x2,boot.gpu_renderer.clip_y2,boot.gpu_renderer.faulted);
        {
            const MusashiGpuFill *fill=&boot.gpu_renderer.last_fill;
            uint16_t row[1024];
            uint64_t checked=0, mismatches=0;
            int readable=boot.gpu_renderer.completed_fills != 0;
            for (unsigned y=0;readable && y<fill->height;++y) {
                readable=musashi_gpu_psycross_read_vram(&boot.gpu_renderer,0,
                    (fill->y+y)&511u,1024,1,row,1024);
                if (!readable) break;
                for (unsigned x=0;x<fill->width;++x) {
                    ++checked;
                    mismatches += row[(fill->x+x)&1023u] != fill->color;
                }
            }
            fprintf(stderr,"native_boot: GPU_FILL controller_completed=%llu backend_completed=%llu "
                    "controller_pixels=%llu backend_pixels=%llu pending_words=%u "
                    "command=%08x xy=%08x wh=%08x x=%u y=%u width=%u height=%u color=%04x "
                    "vram_readable=%d checked=%llu mismatches=%llu\n",
                    (unsigned long long)boot.gpu.completed_fills,
                    (unsigned long long)boot.gpu_renderer.completed_fills,
                    (unsigned long long)boot.gpu.filled_pixels,
                    (unsigned long long)boot.gpu_renderer.filled_pixels,boot.gpu.fill_words,
                    fill->command,fill->xy,fill->wh,fill->x,fill->y,fill->width,fill->height,fill->color,
                    readable,(unsigned long long)checked,(unsigned long long)mismatches);
            for (unsigned i=0;i<6;++i) {
                uint32_t value=0, address=0x80078830u+4u*i;
                int valid=musashi_boot_read32(&boot.memory,address,&value);
                fprintf(stderr,"native_boot: CLEAR_PACKET address=%08x valid=%d value=%08x\n",
                        address,valid,value);
            }
        }
        {
            const uint8_t *cache=musashi_boot_ram_span(&boot.memory,0x80078879u,1);
            fprintf(stderr,"native_boot: DISPLAY_CACHE opcode=05 address=80078879 "
                    "valid=%d value=%02x\n",cache!=NULL,cache ? *cache : 0);
        }
    }
    observe_gpu_dma(&boot,"STOP");
    {
        int removed=musashi_gpu_dma2_close(boot.gpu_dma);
        if (removed) boot.gpu_dma=NULL;
        fprintf(stderr,"native_boot: GPU_DMA2 removed=%d\n",removed);
        if (!removed) cleanup_ok=0;
    }
    dump_display_vram(&boot);
    presentation_ok = musashi_gpu_psycross_present(&boot.gpu_renderer);
    hold_window(&boot);
    gpu_removed = musashi_gpu_psycross_shutdown(&boot.gpu_renderer);
    fprintf(stderr, "native_boot: graphics_init=%s blank_presented=%d gpu_removed=%d\n",
            boot.graphics_returned ? "RETURNED" : "PARTIAL",
            presentation_ok, gpu_removed);
    if (!gpu_removed || !presentation_ok) cleanup_ok = 0;
    if (!musashi_device_epoch_shutdown(&boot.epoch)) cleanup_ok = 0;
    {
        int devices_removed = native_devices_shutdown(&boot);
        fprintf(stderr, "native_boot: OWNED_DEVICES removed=%d\n", devices_removed);
        if (!devices_removed) cleanup_ok = 0;
    }
    PsyX_Shutdown();
    if (!cleanup_ok)
        fputs("native_boot: scheduler removal refused\n", stderr);
    /* The CPU path is proven to stop at the refusal boundary, so no menu was
     * reached. The presented frame still needs a human look, which is a
     * separate claim and is therefore a separate marker. */
    fputs("native_boot: startup=PARTIAL incoming_ra=NATIVE_ZERO menu=NOT_REACHED"
          " visual_check=REQUIRED\n", stderr);
    return host_stop_signal ? 128 + host_stop_signal : 2;
}
