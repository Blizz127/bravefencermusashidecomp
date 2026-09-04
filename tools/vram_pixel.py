#!/usr/bin/env python3
"""PS1 VRAM pixel packing, and the render check's report format.

VRAM is 16 bits per pixel: red in bits 0-4, green in 5-9, blue in 10-14, and
bit 15 as the mask/semi-transparency flag. Pinning this matters because getting
the order backwards compares blue against red and still looks plausible.

The render target itself runs under a display and prints the pixels it sampled;
this module is the pure half, so the packing and the verdict are unit-tested
without needing a GPU.
"""

from __future__ import annotations

import re

from retail_common import RetailError

COMPONENT_MAX = 31
MASK_BIT = 0x8000

REPORT_RE = re.compile(r"^PIXEL\s+(?P<name>\w+)\s+0x(?P<value>[0-9a-fA-F]{1,4})\s*$")
REQUIRED_SAMPLES = ("inside", "outside")


def decode(value: int) -> tuple[int, int, int]:
    """Split a 16-bit VRAM pixel into 5-bit red, green and blue."""

    return (value & 0x1F, (value >> 5) & 0x1F, (value >> 10) & 0x1F)


def encode(red: int, green: int, blue: int) -> int:
    """Pack 5-bit components into a VRAM pixel, without the mask bit."""

    for name, component in (("red", red), ("green", green), ("blue", blue)):
        if not 0 <= component <= COMPONENT_MAX:
            raise RetailError(f"{name} component {component} is outside 0..{COMPONENT_MAX}")
    return red | (green << 5) | (blue << 10)


def from_rgb8(red: int, green: int, blue: int) -> int:
    """Pack an 8-bit colour, as passed to setRGB0, into a VRAM pixel.

    The GPU keeps the top five bits of each component, so 248 and 255 both
    become 31 and a test must compare against the narrowed value.
    """

    return encode(red >> 3, green >> 3, blue >> 3)


def parse_report(output: str) -> dict[str, int]:
    """Read the render target's `PIXEL <name> 0x<value>` lines."""

    samples: dict[str, int] = {}
    for line in output.splitlines():
        match = REPORT_RE.match(line.strip())
        if match:
            samples[match.group("name")] = int(match.group("value"), 16)
    missing = [name for name in REQUIRED_SAMPLES if name not in samples]
    if missing:
        raise RetailError(
            f"render report is missing {', '.join(missing)}; got {sorted(samples) or 'nothing'}"
        )
    return samples
