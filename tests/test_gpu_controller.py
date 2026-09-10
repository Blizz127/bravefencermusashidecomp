"""Checked initial GP0/GP1 frontend with an explicit renderer backend."""
import ctypes as C
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
GPUREAD = 0x1F801810
GPUSTAT = 0x1F801814
UINT32 = C.c_uint32

RESET = C.CFUNCTYPE(C.c_int, C.c_void_p)
DRAW_MODE = C.CFUNCTYPE(C.c_int, C.c_void_p, UINT32)
DISPLAY_ENABLE = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_int)
CLEAR_FIFO = C.CFUNCTYPE(C.c_int, C.c_void_p)
READY = C.CFUNCTYPE(C.c_int, C.c_void_p)
ENVIRONMENT = C.CFUNCTYPE(C.c_int, C.c_void_p, UINT32)
DISPLAY = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_void_p)


class DisplayState(C.Structure):
    _fields_ = [
        ("origin", UINT32), ("horizontal", UINT32), ("vertical", UINT32),
        ("mode", UINT32), ("x", C.c_uint16), ("y", C.c_uint16),
        ("width", C.c_uint16), ("height", C.c_uint16),
        ("h_start", C.c_uint16), ("h_end", C.c_uint16),
        ("v_start", C.c_uint16), ("v_end", C.c_uint16),
        ("dot_divisor", C.c_uint8),
    ]


class Fill(C.Structure):
    _fields_ = [("command", UINT32), ("xy", UINT32), ("wh", UINT32),
                ("x", C.c_uint16), ("y", C.c_uint16),
                ("width", C.c_uint16), ("height", C.c_uint16),
                ("color", C.c_uint16)]


FILL = C.CFUNCTYPE(C.c_int, C.c_void_p, C.POINTER(Fill))
STORE = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_uint16, C.c_uint16, C.c_uint16)
READ = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_uint16, C.c_uint16, C.POINTER(C.c_uint16))


class Backend(C.Structure):
    _fields_ = [("userdata", C.c_void_p), ("reset", RESET),
                ("draw_mode", DRAW_MODE), ("display_enable", DISPLAY_ENABLE),
                ("clear_fifo", CLEAR_FIFO), ("ready", READY),
                ("environment", ENVIRONMENT), ("display", DISPLAY),
                ("fill_vram", FILL), ("store_vram", STORE), ("read_vram", READ)]


class Controller(C.Structure):
    _fields_ = [("backend", Backend), ("read_latch", UINT32),
                ("draw_mode", UINT32), ("dma_direction", UINT32),
                ("display_disabled", C.c_int), ("faulted", C.c_int),
                ("executing", C.c_int), ("vblank_parity", UINT32),
                ("texture_window", UINT32), ("drawing_area_start", UINT32),
                ("drawing_area_end", UINT32), ("drawing_offset", UINT32),
                ("mask_flags", UINT32), ("accepted_gp0_words", C.c_uint64),
                ("display", DisplayState), ("fill_command", UINT32), ("fill_xy", UINT32),
                ("fill_words", C.c_uint8), ("completed_fills", C.c_uint64),
                ("filled_pixels", C.c_uint64), ("last_fill", Fill),
                ("store_command", UINT32), ("store_xy", UINT32),
                ("store_wh", UINT32), ("store_x", C.c_uint16),
                ("store_y", C.c_uint16), ("store_w", C.c_uint16),
                ("store_h", C.c_uint16), ("store_px", C.c_uint16),
                ("store_py", C.c_uint16), ("store_remaining", UINT32),
                ("store_phase", C.c_uint8), ("stored_pixels", C.c_uint64),
                ("copy_command", UINT32), ("copy_src", UINT32),
                ("copy_dst", UINT32), ("copy_words", C.c_uint8),
                ("copied_pixels", C.c_uint64), ("completed_copies", C.c_uint64),
                ("prim_needed", C.c_uint8), ("prim_got", C.c_uint8),
                ("prim_data", UINT32 * 12), ("drawn_pixels", C.c_uint64)]


class GpuControllerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        temp = tempfile.TemporaryDirectory(prefix="musashi-gpu-controller-")
        cls.addClassCleanup(temp.cleanup)
        library = Path(temp.name) / "gpu_controller.so"
        subprocess.run([
            "cc", "-std=c99", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            "-I", str(ROOT / "pc_port/include"),
            str(ROOT / "pc_port/gpu_controller.c"), "-o", str(library),
        ], check=True, stdin=subprocess.DEVNULL, timeout=30)
        cls.lib = C.CDLL(str(library))
        cls.lib.musashi_gpu_controller_init.argtypes = [
            C.POINTER(Controller), C.POINTER(Backend)]
        cls.lib.musashi_gpu_controller_read32.argtypes = [
            C.POINTER(Controller), UINT32, C.POINTER(UINT32)]
        cls.lib.musashi_gpu_controller_write32.argtypes = [
            C.POINTER(Controller), UINT32, UINT32]
        cls.lib.musashi_gpu_controller_vblank.argtypes = [
            C.POINTER(Controller)]

    def setUp(self):
        self.controller = Controller()
        self.ready_value = 1
        self.calls = []

        def reset(_):
            self.calls.append(("reset",))
            return 1

        def draw_mode(_, word):
            self.calls.append(("draw_mode", word))
            return 1

        def display_enable(_, enabled):
            self.calls.append(("display_enable", enabled))
            return 1

        def clear_fifo(_):
            self.calls.append(("clear_fifo",))
            return 1

        def ready(_):
            self.calls.append(("ready",))
            return self.ready_value

        def environment(_, word):
            self.calls.append(("environment", word))
            return 1

        def display(_, candidate):
            state = C.cast(candidate, C.POINTER(DisplayState)).contents
            self.calls.append(("display", state.mode, state.width, state.height))
            return 1

        self.callbacks = (RESET(reset), DRAW_MODE(draw_mode),
                          DISPLAY_ENABLE(display_enable), CLEAR_FIFO(clear_fifo),
                          READY(ready), ENVIRONMENT(environment), DISPLAY(display))
        self.backend = Backend(None, *self.callbacks)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(self.controller), C.byref(self.backend)), 1)

    def test_fill_partial_packet_and_real_descriptor(self):
        fills = []
        def accept(_, candidate):
            f = candidate.contents
            fills.append((f.command, f.xy, f.wh, f.x, f.y,
                          f.width, f.height, f.color))
            return 1
        fill = FILL(accept)
        self.controller.backend.fill_vram = fill
        self.assertEqual(self.write(0x02ff00ff), 1)
        self.assertEqual(self.controller.fill_words, 1)
        self.assertEqual(self.controller.accepted_gp0_words, 1)
        self.assertEqual(fills, [])
        self.assertEqual(self.read()[1] & (1 << 26), 0)
        self.assertNotEqual(self.read()[1] & (1 << 28), 0)
        self.assertEqual(self.write(0xe60003ff), 1)  # data, not E6
        self.assertEqual(self.controller.mask_flags, 0)
        self.assertEqual(self.controller.fill_words, 2)
        self.assertEqual(fills, [])
        self.assertEqual(self.write(0x01ff0011), 1)
        self.assertEqual(fills, [(0x02ff00ff, 0xe60003ff, 0x01ff0011,
                                 1008, 0, 32, 511, 0x7c1f)])
        self.assertEqual(self.controller.fill_words, 0)
        self.assertEqual(self.controller.completed_fills, 1)
        self.assertEqual(self.controller.filled_pixels, 32 * 511)
        self.assertEqual(self.controller.accepted_gp0_words, 3)

    def test_fill_reset_refusal_and_accepted_reentry(self):
        for prefix in (1, 2):
            for reset_word in (0, 0x01000000):
                self.setUp()
                calls = []
                fill = FILL(lambda _, f: calls.append(f.contents.color) or 1)
                self.controller.backend.fill_vram = fill
                self.assertEqual(self.write(0x02ffffff), 1)
                if prefix == 2:
                    self.assertEqual(self.write(0), 1)
                self.assertEqual(self.write(reset_word, GPUSTAT), 1)
                self.assertEqual(self.controller.fill_words, 0)
                self.assertEqual(self.controller.accepted_gp0_words, prefix)
                self.assertEqual(calls, [])
                self.assertEqual(self.write(0xe6000003), 1)
                self.assertEqual(self.controller.mask_flags, 3)
        for accept in (False, True):
            self.setUp()
            calls = []
            def backend(_, f):
                calls.append(f.contents.color)
                if accept:
                    self.assertEqual(self.write(0xe1000000), 0)
                return int(accept)
            fill = FILL(backend)
            self.controller.backend.fill_vram = fill
            self.assertEqual(self.write(0x020000ff), 1)
            self.assertEqual(self.write(0), 1)
            self.assertEqual(self.write(0x00010010), 0)
            self.assertEqual(calls, [31])
            self.assertEqual(self.controller.faulted, 1)
            self.assertEqual(self.controller.accepted_gp0_words, 3 if accept else 2)
            self.assertEqual(self.controller.completed_fills, int(accept))
            self.assertEqual(self.controller.fill_words, 0 if accept else 2)

    def test_fill_busy_counter_and_zero_extent(self):
        calls = []
        fill = FILL(lambda _, f: calls.append(f.contents.color) or 1)
        self.controller.backend.fill_vram = fill
        self.assertEqual(self.write(0x0200ff00), 1)
        self.ready_value = 0
        self.assertEqual(self.write(0xe6000003), 0)
        self.assertEqual(self.controller.fill_words, 1)
        self.assertEqual(self.controller.faulted, 0)
        self.ready_value = 1
        self.assertEqual(self.write(0), 1)
        self.controller.completed_fills = (1 << 64) - 1
        self.assertEqual(self.write(0x00010010), 0)
        self.assertEqual(calls, [])
        self.assertEqual(self.controller.fill_words, 2)
        self.controller.completed_fills = 0
        self.assertEqual(self.write(0x02000400), 1)  # both effective sizeszero
        self.assertEqual(calls, [0x3e0])
        self.assertEqual(self.controller.filled_pixels, 0)
        self.assertEqual(self.controller.completed_fills, 1)
        self.assertEqual(self.controller.accepted_gp0_words, 3)

    def read(self, address=GPUSTAT):
        value = UINT32(0xDEADBEEF)
        accepted = self.lib.musashi_gpu_controller_read32(
            C.byref(self.controller), address, C.byref(value))
        return accepted, value.value

    def write(self, value, address=GPUREAD):
        return self.lib.musashi_gpu_controller_write32(
            C.byref(self.controller), address, value)

    def vblank(self, controller=None):
        target = self.controller if controller is None else controller
        return self.lib.musashi_gpu_controller_vblank(C.byref(target))

    def test_init_requires_reset_acceptance_and_starts_guest_reset_state(self):
        self.assertEqual(self.controller.read_latch, 0x400)
        self.assertEqual(self.controller.draw_mode, 0)
        self.assertEqual(self.controller.display_disabled, 1)
        self.assertEqual(self.controller.dma_direction, 0)
        self.assertEqual(self.controller.faulted, 0)
        self.assertEqual(self.controller.vblank_parity, 0)
        self.assertEqual(self.calls, [("reset",)])

        failed = Controller()
        self.ready_value = 0
        self.callbacks[0]  # keep callback tuple alive while replacing backend
        refused = RESET(lambda _: 0)
        bad_backend = Backend(None, refused, self.callbacks[1],
                              self.callbacks[2], self.callbacks[3], self.callbacks[4],
                              self.callbacks[5])
        before = bytes(failed)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(failed), C.byref(bad_backend)), 0)
        self.assertEqual(bytes(failed), before)
        self.assertEqual(failed.faulted, 0)
        self.assertEqual(failed.executing, 0)
        self.assertEqual(failed.accepted_gp0_words, 0)

    def test_gp1_display_05_to_08_commit_ordered_descriptor_and_status(self):
        self.assertEqual(self.controller.display.origin, 0)
        self.assertEqual(self.controller.display.horizontal, 0x00C00200)
        self.assertEqual(self.controller.display.vertical, 0x00040010)
        self.assertEqual(self.controller.display.width, 256)
        self.assertEqual(self.controller.display.height, 240)
        self.assertEqual(self.controller.display.dot_divisor, 10)
        self.assertEqual(self.write(0x05000000, GPUSTAT), 1)
        self.assertEqual(self.write(0x06C60260, GPUSTAT), 1)
        self.assertEqual(self.controller.display.width, 256)
        self.assertEqual(self.write(0x07040010, GPUSTAT), 1)
        self.assertEqual(self.write(0x08000001, GPUSTAT), 1)
        self.assertEqual(self.controller.display.mode, 1)
        self.assertEqual(self.controller.display.width, 320)
        self.assertEqual(self.controller.display.dot_divisor, 8)
        self.assertEqual(self.calls[-1], ("display", 1, 320, 240))
        accepted, status = self.read(GPUSTAT)
        self.assertEqual(accepted, 1)
        self.assertEqual((status >> 17) & 3, 1)
        self.assertEqual(status & (0xf << 19), 0)

    def test_gp1_display_rejects_unsupported_range_or_mode_transactionally(self):
        before = bytes(self.controller)
        self.assertEqual(self.write(0x07040020, GPUSTAT), 0)
        self.assertEqual(bytes(self.controller), before)
        self.assertEqual(self.write(0x08000008, GPUSTAT), 0)
        self.assertEqual(bytes(self.controller), before)

    def test_interlaced_480_line_scanout_covers_both_fields(self):
        self.assertEqual(self.write(0x06C60260, GPUSTAT), 1)
        for mode, height in ((0x03, 240), (0x07, 240), (0x23, 240), (0x27, 480), (0x01, 240)):
            self.assertEqual(self.write(0x08000000 | mode, GPUSTAT), 1)
            self.assertEqual(self.controller.display.height, height, hex(mode))
            self.assertEqual(self.calls[-1][3], height)

    def test_gp1_display_mode_map_and_status_bits_for_all_byte_values(self):
        supported = {}
        for mode in range(256):
            if mode & 0x98:
                continue
            if (mode & 0x40) and (mode & 3):
                continue
            if mode & 0x40:
                supported[mode] = 7
            else:
                supported[mode] = {0: 10, 1: 8, 2: 5, 3: 4}[mode & 3]
        for mode in range(256):
            before = bytes(self.controller)
            accepted = self.write(0x08000000 | mode, GPUSTAT)
            if mode not in supported:
                self.assertEqual(accepted, 0, hex(mode))
                self.assertEqual(bytes(self.controller), before)
                continue
            self.assertEqual(accepted, 1, hex(mode))
            self.assertEqual(self.controller.display.mode, mode)
            self.assertEqual(self.controller.display.dot_divisor, supported[mode])
            _, status = self.read(GPUSTAT)
            self.assertEqual((status >> 17) & 3, mode & 3)
            self.assertEqual((status >> 19) & 0xf, (mode >> 2) & 0xf)
            self.assertEqual((status >> 16) & 1, (mode >> 6) & 1)

    def test_gp1_display_origin_masks_upper_payload_bits(self):
        self.assertEqual(self.write(0x05081234, GPUSTAT), 1)
        self.assertEqual(self.controller.display.origin, 0x1234)
        self.assertEqual(self.controller.display.x, 0x234)
        self.assertEqual(self.controller.display.y, 0x4)

    def test_gp1_display_horizontal_rounding_and_bounds_refuse_atomically(self):
        self.assertEqual(self.write(0x06C60260, GPUSTAT), 1)
        self.assertEqual(self.write(0x06020002, GPUSTAT), 1)
        self.assertEqual(self.controller.display.width, 4)
        before = bytes(self.controller)
        for payload in (0x00020200, 0x00200200):
            self.assertEqual(self.write(0x06000000 | payload, GPUSTAT), 0)
            self.assertEqual(bytes(self.controller), before)
        self.assertEqual(self.write(0x060C0260, GPUSTAT), 0)
        self.assertEqual(bytes(self.controller), before)

    def test_gp1_display_clear_fifo_preserves_and_reset_restores_descriptor(self):
        for value in (0x05000123, 0x06C60260, 0x07040010, 0x08000001):
            self.assertEqual(self.write(value, GPUSTAT), 1)
        before = bytes(self.controller.display)
        self.assertEqual(self.write(0x01000000, GPUSTAT), 1)
        self.assertEqual(bytes(self.controller.display), before)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.controller.display.origin, 0)
        self.assertEqual(self.controller.display.horizontal, 0x00C00200)
        self.assertEqual(self.controller.display.width, 256)

    def test_gp1_display_missing_capability_refuses_without_mutation(self):
        fresh = Controller()
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          self.callbacks[5])
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        before = bytes(fresh)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUSTAT, 0x05000123), 0)
        self.assertEqual(bytes(fresh), before)

    def test_gp1_display_provider_refusal_preserves_frontend_descriptor(self):
        fresh = Controller()

        def refuse(_, candidate):
            return 0

        refused = DISPLAY(refuse)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          self.callbacks[5], refused)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        before = bytes(fresh.display)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUSTAT, 0x05000123), 0)
        self.assertEqual(bytes(fresh.display), before)
        self.assertEqual(fresh.faulted, 1)

    def test_gp1_display_ready_reentry_refuses_before_provider(self):
        fresh = Controller()
        nested = []

        def reentrant_ready(_):
            nested.append(self.lib.musashi_gpu_controller_write32(
                C.byref(fresh), GPUSTAT, 0x05000123))
            return 1

        callback = READY(reentrant_ready)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], callback,
                          self.callbacks[5], self.callbacks[6])
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        before = bytes(fresh.display)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUSTAT, 0x05000123), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(bytes(fresh.display), before)
        self.assertEqual(fresh.faulted, 1)

    def test_gp1_display_provider_reentry_retains_accepted_descriptor_and_fault(self):
        fresh = Controller()
        nested = []

        def reentrant_display(_, candidate):
            nested.append(self.lib.musashi_gpu_controller_write32(
                C.byref(fresh), GPUSTAT, 0x05000123))
            return 1

        callback = DISPLAY(reentrant_display)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          self.callbacks[5], callback)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUSTAT, 0x05000123), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(fresh.display.origin, 0x123)
        self.assertEqual(fresh.faulted, 1)

    def test_constructor_reset_reentry_refuses_publication(self):
        fresh = Controller()
        holder = {}
        nested = []

        def nested_reset(_):
            nested.append(self.lib.musashi_gpu_controller_init(
                C.byref(fresh), C.byref(holder["backend"])))
            return 1

        reset_callback = RESET(nested_reset)
        holder["backend"] = Backend(None, reset_callback, self.callbacks[1],
                                     self.callbacks[2], self.callbacks[3],
                                     self.callbacks[4], self.callbacks[5])
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(holder["backend"])), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(fresh.faulted, 1)
        self.assertEqual(fresh.executing, 0)
        self.assertEqual(fresh.accepted_gp0_words, 0)

    def test_gpu_read_latch_and_info_index_seven_leave_400_unchanged(self):
        self.assertEqual(self.read(GPUREAD), (1, 0x400))
        self.assertEqual(self.write(0x10000007, GPUSTAT), 1)
        self.assertEqual(self.calls, [("reset",)])
        self.assertEqual(self.read(GPUREAD), (1, 0x400))
        self.assertEqual(self.calls[-1], ("reset",))

    def test_gp0_nop_does_not_call_renderer_or_reset(self):
        before = bytes(self.controller)
        self.assertEqual(self.write(0x0007924C), 1)
        self.assertNotEqual(bytes(self.controller), before)
        self.assertEqual(self.controller.accepted_gp0_words, 1)
        self.assertEqual(self.calls, [("reset",), ("ready",)])

    def test_gp0_draw_mode_uses_backend_and_maps_only_supported_status_bits(self):
        word = 0xE1F23ABC
        self.assertEqual(self.write(word), 1)
        self.assertEqual(self.calls[-2:], [("ready",), ("draw_mode", word)])
        self.assertEqual(self.controller.draw_mode, word & 0x3FFF)
        accepted, status = self.read()
        self.assertEqual(accepted, 1)
        self.assertEqual(status & 0x7FF, word & 0x7FF)
        self.assertEqual(status & 0x8000, 0x8000 if word & 0x800 else 0)
        self.assertEqual(status & 0x1000, 0)

    def test_environment_words_commit_raw_latches_and_status_mask_bits(self):
        words = (0xE2123456, 0xE30ABCDE, 0xE41ABCDE,
                 0xE5123456, 0xE6000003)
        for word in words:
            self.assertEqual(self.write(word), 1)
        self.assertEqual(self.controller.texture_window, words[0] & 0xFFFFF)
        self.assertEqual(self.controller.drawing_area_start, words[1] & 0xFFFFF)
        self.assertEqual(self.controller.drawing_area_end, words[2] & 0xFFFFF)
        self.assertEqual(self.controller.drawing_offset, words[3] & 0x3FFFFF)
        self.assertEqual(self.controller.mask_flags, 3)
        self.assertEqual(self.controller.accepted_gp0_words, 5)
        self.assertEqual(self.write(0x10000002, GPUSTAT), 1)
        self.assertEqual(self.read(GPUREAD), (1, words[0] & 0xFFFFF))
        self.assertEqual(self.write(0x10000005, GPUSTAT), 1)
        self.assertEqual(self.read(GPUREAD), (1, words[3] & 0x3FFFFF))
        _, status = self.read()
        self.assertEqual(status & ((1 << 11) | (1 << 12)),
                         (1 << 11) | (1 << 12))

    def test_e2_preserves_noncontiguous_masks_and_offsets_outside_mask(self):
        raw = ((0b10101) | (0b01010 << 5) |
               (0b11100 << 10) | (0b00011 << 15))
        self.assertEqual(self.write(0xE2000000 | raw), 1)
        self.assertEqual(self.controller.texture_window, raw)
        self.assertEqual(self.write(0x10000002, GPUSTAT), 1)
        self.assertEqual(self.read(GPUREAD), (1, raw))

    def test_e5_exercises_every_independent_signed_11_bit_component(self):
        for x in range(2048):
            self.assertEqual(self.write(0xE5000000 | x), 1)
            self.assertEqual(self.controller.drawing_offset, x)
        for y in range(2048):
            self.assertEqual(self.write(0xE5000000 | (y << 11)), 1)
            self.assertEqual(self.controller.drawing_offset, y << 11)
        self.assertEqual((2047 if 2047 < 1024 else 2047 - 2048), -1)
        self.assertEqual((1023 if 1023 < 1024 else 1023 - 2048), 1023)

    def test_e6_all_force_and_check_flag_combinations_map_gpu_status(self):
        for flags in range(4):
            self.assertEqual(self.write(0xE6000000 | flags), 1)
            _, status = self.read()
            self.assertEqual((status >> 11) & 3, flags)

    def test_e3_e4_raw_queries_keep_twenty_bits_and_latch_until_next_query(self):
        start = 0x80000 | (7 << 10) | 2
        end = (511 << 10) | 1023
        self.assertEqual(self.write(0xE3000000 | start), 1)
        self.assertEqual(self.write(0xE4000000 | end), 1)
        self.assertEqual(self.write(0x10000003, GPUSTAT), 1)
        self.assertEqual(self.read(GPUREAD), (1, start))
        self.assertEqual(self.write(0xE3000000 | 0x123), 1)
        self.assertEqual(self.read(GPUREAD), (1, start))
        self.assertEqual(self.write(0x10000004, GPUSTAT), 1)
        self.assertEqual(self.read(GPUREAD), (1, end))

    def test_gp1_reset_preserves_accepted_count_but_clears_environment(self):
        self.assertEqual(self.write(0xE2123456), 1)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.controller.accepted_gp0_words, 1)
        self.assertEqual(self.controller.texture_window, 0)
        self.assertEqual(self.controller.mask_flags, 0)

    def test_environment_without_backend_callback_refuses_without_mutation(self):
        fresh = Controller()
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          ENVIRONMENT())
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        before = bytes(fresh)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE2000000), 0)
        self.assertEqual(bytes(fresh), before)

    def test_environment_backend_refusal_is_sticky_and_preserves_raw_register(self):
        fresh = Controller()

        def refuse_environment(_, word):
            self.calls.append(("environment_refused", word))
            return 0

        callback = ENVIRONMENT(refuse_environment)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          callback)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE2000001), 0)
        self.assertEqual(fresh.faulted, 1)
        self.assertEqual(fresh.texture_window, 0)
        self.assertEqual(fresh.accepted_gp0_words, 0)

    def test_environment_backend_reentry_commits_word_but_faults_outer_call(self):
        fresh = Controller()
        nested = []

        def environment(_, word):
            nested.append(self.lib.musashi_gpu_controller_write32(
                C.byref(fresh), GPUREAD, 0xE1000000))
            return 1

        callback = ENVIRONMENT(environment)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], self.callbacks[4],
                          callback)
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE2000001), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(fresh.faulted, 1)
        self.assertEqual(fresh.texture_window, 1)
        self.assertEqual(fresh.accepted_gp0_words, 1)

    def test_ready_reentry_refuses_without_accepting_gp0_word(self):
        fresh = Controller()
        nested = []

        def ready_reentrant(_):
            nested.append(self.lib.musashi_gpu_controller_write32(
                C.byref(fresh), GPUREAD, 0xE1000000))
            return 1

        callback = READY(ready_reentrant)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], callback,
                          self.callbacks[5])
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE1000000), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(fresh.faulted, 1)
        self.assertEqual(fresh.accepted_gp0_words, 0)

    def test_gp0_counter_overflow_refuses_before_backend_callback(self):
        self.controller.accepted_gp0_words = (1 << 64) - 1
        before_calls = list(self.calls)
        before = bytes(self.controller)
        self.assertEqual(self.write(0xE1000000), 0)
        self.assertEqual(self.calls, before_calls)
        self.assertEqual(bytes(self.controller), before)

    def test_busy_gp0_refuses_without_command_effects_and_ready_bits_clear(self):
        self.ready_value = 0
        before = bytes(self.controller)
        self.assertEqual(self.write(0xE1001234), 0)
        self.assertEqual(bytes(self.controller), before)
        accepted, status = self.read()
        self.assertEqual(accepted, 1)
        self.assertEqual(status & ((1 << 26) | (1 << 28)), 0)

    def test_status_maps_display_dma_and_backend_ready_state(self):
        self.assertEqual(self.write(0x03000000, GPUSTAT), 1)
        self.assertEqual(self.controller.display_disabled, 0)
        self.assertEqual(self.write(0x04000002, GPUSTAT), 1)
        _, status = self.read()
        self.assertEqual(status & (1 << 23), 0)
        self.assertEqual((status >> 29) & 3, 2)
        self.assertEqual(status & (1 << 25), 1 << 25)
        self.ready_value = 0
        _, status = self.read()
        self.assertEqual(status & ((1 << 26) | (1 << 28) | (1 << 25)), 0)
        self.assertEqual(self.write(0x03000001, GPUSTAT), 1)
        self.assertEqual(self.controller.display_disabled, 1)
        self.assertEqual(self.calls[-1], ("display_enable", 0))

    def test_gp1_reset_fifo_ack_display_and_dma_controls_are_checked(self):
        self.controller.read_latch = 99
        self.controller.draw_mode = 0x3FFF
        self.controller.display_disabled = 0
        self.controller.dma_direction = 3
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.controller.read_latch, 0x400)
        self.assertEqual(self.controller.draw_mode, 0)
        self.assertEqual(self.controller.display_disabled, 1)
        self.assertEqual(self.controller.dma_direction, 0)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)

    def test_vblank_toggles_gpu_status_odd_even_bit_once_per_edge(self):
        self.assertEqual(self.read()[1] & (1 << 31), 0)
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.controller.vblank_parity, 1)
        self.assertEqual(self.read()[1] & (1 << 31), 1 << 31)
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.controller.vblank_parity, 0)
        self.assertEqual(self.read()[1] & (1 << 31), 0)

    def test_two_coalesced_source_edges_toggle_parity_twice(self):
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.controller.vblank_parity, 0)
        self.assertEqual(self.read()[1] & (1 << 31), 0)

    def test_vblank_does_not_require_ready_backend_for_blank_edge(self):
        self.ready_value = 0
        self.assertEqual(self.calls, [("reset",)])
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.calls, [("reset",), ("ready",)])
        accepted, status = self.read()
        self.assertEqual(accepted, 1)
        self.assertEqual(status & (1 << 31), 1 << 31)
        self.assertEqual(status & ((1 << 26) | (1 << 28) | (1 << 25)), 0)

    def test_gp1_reset_clears_vblank_parity_to_source_reset_value(self):
        self.assertEqual(self.vblank(), 1)
        self.assertEqual(self.write(0x00000000, GPUSTAT), 1)
        self.assertEqual(self.controller.vblank_parity, 0)
        accepted, status = self.read()
        self.assertEqual(accepted, 1)
        self.assertEqual(status, 0x14802000)

    def test_vblank_refuses_invalid_owner_without_moving_prior_parity(self):
        self.controller.vblank_parity = 1
        self.controller.faulted = 1
        self.assertEqual(self.vblank(), 0)
        self.assertEqual(self.controller.vblank_parity, 1)
        self.controller.faulted = 0
        self.controller.executing = 1
        self.assertEqual(self.vblank(), 0)
        self.assertEqual(self.controller.vblank_parity, 1)

        fresh = Controller()
        self.assertEqual(self.vblank(fresh), 0)
        self.assertEqual(fresh.vblank_parity, 0)

        def refuse_ready(_):
            self.calls.append(("ready_refused",))
            return -1

        refused_ready = READY(refuse_ready)
        backend = Backend(None, self.callbacks[0], self.callbacks[1],
                          self.callbacks[2], self.callbacks[3], refused_ready)
        refused = Controller()
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(refused), C.byref(backend)), 1)
        refused.vblank_parity = 1
        self.assertEqual(self.lib.musashi_gpu_controller_vblank(
            C.byref(refused)), 0)
        self.assertEqual(refused.faulted, 1)
        self.assertEqual(refused.vblank_parity, 1)
        output = UINT32(0xDEADBEEF)
        self.assertEqual(self.lib.musashi_gpu_controller_read32(
            C.byref(refused), GPUSTAT, C.byref(output)), 0)
        self.assertEqual(refused.faulted, 1)
        self.assertEqual(output.value, 0xDEADBEEF)
        self.assertEqual(refused.vblank_parity, 1)

    def test_backend_refusal_faults_controller_and_blocks_later_access(self):
        def refuse_draw(_, word):
            self.calls.append(("draw_refused", word))
            return 0

        refusal = DRAW_MODE(refuse_draw)
        backend = Backend(None, self.callbacks[0], refusal, self.callbacks[2],
                          self.callbacks[3], self.callbacks[4])
        fresh = Controller()
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE1000000), 0)
        self.assertEqual(fresh.faulted, 1)
        output = UINT32(0xDEADBEEF)
        self.assertEqual(self.lib.musashi_gpu_controller_read32(
            C.byref(fresh), GPUSTAT, C.byref(output)), 0)
        self.assertEqual(output.value, 0xDEADBEEF)

    def test_unsupported_commands_and_addresses_refuse_without_effects(self):
        before = bytes(self.controller)
        for value, address in ((0x20000000, GPUREAD),
                               (0x09000000, GPUSTAT)):
            self.assertEqual(self.write(value, address), 0)
            self.assertEqual(bytes(self.controller), before)
        self.assertEqual(self.write(0x06000001, GPUSTAT), 0)
        self.assertEqual(bytes(self.controller), before)
        output = UINT32(0xDEADBEEF)
        self.assertEqual(self.lib.musashi_gpu_controller_read32(
            C.byref(self.controller), 0x1F801818, C.byref(output)), 0)
        self.assertEqual(output.value, 0xDEADBEEF)
        self.assertEqual(self.write(0, 0x1F801818), 0)

    def test_uninitialized_controller_refuses_without_calling_unbound_backend(self):
        fresh = Controller()
        output = UINT32(0xDEADBEEF)
        self.assertEqual(self.lib.musashi_gpu_controller_read32(
            C.byref(fresh), GPUSTAT, C.byref(output)), 0)
        self.assertEqual(output.value, 0xDEADBEEF)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUSTAT, 0x02000000), 0)

    def test_backend_callbacks_cannot_reenter_writes_and_see_ready_during_execution(self):
        fresh = Controller()
        nested = []

        def nested_draw(_, word):
            fresh.dma_direction = 1
            nested.append(self.lib.musashi_gpu_controller_write32(
                C.byref(fresh), GPUREAD, word))
            output = UINT32(0xDEADBEEF)
            self.assertEqual(self.lib.musashi_gpu_controller_read32(
                C.byref(fresh), GPUSTAT, C.byref(output)), 0)
            self.assertEqual(output.value, 0xDEADBEEF)
            return 1

        callback = DRAW_MODE(nested_draw)
        backend = Backend(None, self.callbacks[0], callback, self.callbacks[2],
                          self.callbacks[3], self.callbacks[4], self.callbacks[5])
        self.assertEqual(self.lib.musashi_gpu_controller_init(
            C.byref(fresh), C.byref(backend)), 1)
        self.assertEqual(self.lib.musashi_gpu_controller_write32(
            C.byref(fresh), GPUREAD, 0xE1001234), 0)
        self.assertEqual(nested, [0])
        self.assertEqual(fresh.faulted, 1)


    def test_gp0_clear_cache_is_nop_like_ready_word(self):
        before_calls = list(self.calls)
        self.assertEqual(self.write(0x01000000), 1)
        self.assertEqual(self.controller.accepted_gp0_words, 1)
        self.assertEqual(self.controller.store_phase, 0)
        self.assertEqual(self.calls, before_calls + [("ready",)])

    def test_gp0_cpu_to_vram_writes_each_texel_through_store_vram(self):
        stored = []

        def accept(_, x, y, pixel):
            stored.append((x, y, pixel))
            return 1

        self.store_cb = STORE(accept)
        self.controller.backend.store_vram = self.store_cb
        self.assertEqual(self.write(0xA0000000), 1)
        self.assertEqual(self.controller.store_phase, 1)
        self.assertEqual(self.write(0x00020010), 1)  # y=2 x=16
        self.assertEqual(self.write(0x00020002), 1)  # h=2 w=2
        self.assertEqual(self.controller.store_remaining, 4)
        self.assertEqual(stored, [])
        self.assertEqual(self.write(0x22221111), 1)
        self.assertEqual(stored, [(16, 2, 0x1111), (17, 2, 0x2222)])
        self.assertEqual(self.write(0x44443333), 1)
        self.assertEqual(stored, [
            (16, 2, 0x1111), (17, 2, 0x2222),
            (16, 3, 0x3333), (17, 3, 0x4444)])
        self.assertEqual(self.controller.store_phase, 0)
        self.assertEqual(self.controller.stored_pixels, 4)
        self.assertEqual(self.controller.accepted_gp0_words, 5)

    def test_gp0_cpu_to_vram_payload_is_not_parsed_as_fill(self):
        stored = []

        def accept(_, x, y, pixel):
            stored.append((x, y, pixel))
            return 1

        self.store_cb = STORE(accept)
        self.controller.backend.store_vram = self.store_cb
        self.assertEqual(self.write(0xA0000000), 1)
        self.assertEqual(self.write(0), 1)
        self.assertEqual(self.write(0x00020002), 1)
        self.assertEqual(self.write(0x02000200), 1)
        self.assertEqual(stored, [(0, 0, 0x0200), (1, 0, 0x0200)])
        self.assertEqual(self.controller.fill_words, 0)
        self.assertEqual(self.controller.store_remaining, 2)
        self.assertEqual(self.write(0xA000A000), 1)
        self.assertEqual(stored, [
            (0, 0, 0x0200), (1, 0, 0x0200),
            (0, 1, 0xA000), (1, 1, 0xA000)])
        self.assertEqual(self.controller.store_phase, 0)

    def test_gp0_poly_f4_rasterizes_through_store_vram(self):
        stored = []

        def accept(_, x, y, pixel):
            stored.append((x, y, pixel))
            return 1

        self.store_cb = STORE(accept)
        self.controller.backend.store_vram = self.store_cb
        self.assertEqual(self.write(0xE3000000), 1)
        self.assertEqual(self.write(0xE403C13F), 1)  # 319,240
        self.assertEqual(self.write(0x2AFFFFFF), 1)
        self.assertEqual(self.controller.prim_needed, 5)
        self.assertEqual(self.write(0x00000000), 1)
        self.assertEqual(self.write(0x00000008), 1)
        self.assertEqual(self.write(0x00080000), 1)
        self.assertEqual(self.write(0x00080008), 1)
        self.assertEqual(self.controller.prim_needed, 0)
        self.assertGreater(len(stored), 0)
        self.assertTrue(all(p == 0x7FFF for _, _, p in stored))
        self.assertEqual(self.controller.drawn_pixels, len(stored))

    def test_gp0_cpu_to_vram_without_backend_refuses(self):
        before = bytes(self.controller)
        self.assertEqual(self.write(0xA0000000), 0)
        self.assertEqual(bytes(self.controller), before)


if __name__ == "__main__":
    unittest.main()
