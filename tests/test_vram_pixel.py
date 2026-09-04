from __future__ import annotations

import subprocess
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TOOLS = ROOT / "tools"
sys.path.insert(0, str(TOOLS))

import vram_pixel  # noqa: E402
from retail_common import RetailError  # noqa: E402


class DecodeTests(unittest.TestCase):
    """PS1 VRAM is 16-bit: r in bits 0-4, g in 5-9, b in 10-14, mask in 15.

    The port's render check compares pixels it reads back, so the packing has to
    be pinned. Getting it backwards would compare blue against red and still
    look plausible.
    """

    def test_decodes_pure_red(self) -> None:
        self.assertEqual(vram_pixel.decode(0x001F), (31, 0, 0))

    def test_decodes_pure_green(self) -> None:
        self.assertEqual(vram_pixel.decode(0x03E0), (0, 31, 0))

    def test_decodes_pure_blue(self) -> None:
        self.assertEqual(vram_pixel.decode(0x7C00), (0, 0, 31))

    def test_ignores_the_mask_bit(self) -> None:
        self.assertEqual(vram_pixel.decode(0x801F), (31, 0, 0))

    def test_black_is_zero(self) -> None:
        self.assertEqual(vram_pixel.decode(0x0000), (0, 0, 0))


class EncodeTests(unittest.TestCase):
    def test_round_trips(self) -> None:
        for value in (0x0000, 0x001F, 0x03E0, 0x7C00, 0x1234):
            self.assertEqual(vram_pixel.encode(*vram_pixel.decode(value)), value & 0x7FFF)

    def test_eight_bit_components_are_narrowed_to_five(self) -> None:
        """A colour given to setRGB0 as 0-255 appears in VRAM as 0-31."""
        self.assertEqual(vram_pixel.from_rgb8(248, 0, 0), 0x001F)

    def test_out_of_range_component_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            vram_pixel.encode(32, 0, 0)


class RenderReportTests(unittest.TestCase):
    """The render target prints what it saw; the harness judges it."""

    def test_parses_a_pixel_report(self) -> None:
        out = "PIXEL inside 0x001F\nPIXEL outside 0x0000\n"
        self.assertEqual(
            vram_pixel.parse_report(out), {"inside": 0x001F, "outside": 0x0000}
        )

    def test_a_missing_sample_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            vram_pixel.parse_report("PIXEL inside 0x001F\n")

    def test_garbage_output_is_refused(self) -> None:
        with self.assertRaises(RetailError):
            vram_pixel.parse_report("segfault\n")


if __name__ == "__main__":
    unittest.main()
