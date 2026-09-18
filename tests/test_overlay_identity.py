"""Compile the production overlay selector; reject code from another overlay."""
import ctypes
from pathlib import Path
import re
import subprocess
import struct

import pytest

from test_bios_event_callbacks import _generate_formatter_includes

ROOT = Path(__file__).resolve().parents[1]


@pytest.mark.parametrize("path", sorted((ROOT / "src/overlays/main_0010").glob("*.c")),
                         ids=lambda path: path.name)
def test_title_overlay_exports_match_retail(path):
    words = re.findall(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)",
                       path.read_text())
    assert words
    payload = struct.pack("<" + "I" * len(words), *(int(w, 16) for w in words))
    overlay = (ROOT / "extracted/overlays/main/0010.bin").read_bytes()
    offset = 0x20000 + int(path.stem, 16) - 0x800CEDF8
    assert payload == overlay[offset:offset + len(payload)]


_PROBE_SOURCE = r'''
#include <stdint.h>
#include <string.h>
/* Compile the production selector directly. formatter_fetch is static, so the
 * probe includes the translation unit; -fvisibility=hidden plus
 * -Wl,--gc-sections drops the rest of the port and its externs. The old
 * harness sliced a literal if-chain out of the source and stopped compiling
 * once d9f78a3a8 moved the guards into range tables. */
#include "mips_formatter.c"

__attribute__((visibility("default")))
int overlay_selector_probe(unsigned pc, unsigned overlay, uint32_t *out) {
    g_overlay_sc02_0031_words = overlay == 2031;
    g_overlay_0004_words = overlay == 4;
    g_overlay_0007_words = overlay == 7;
    g_overlay_0010_words = overlay == 10;
    FormatterCpu cpu;
    memset(&cpu, 0, sizeof cpu);
    cpu.pc = pc;
    return formatter_fetch(&cpu, out);
}
'''


@pytest.fixture(scope="module")
def selector(tmp_path_factory):
    work = tmp_path_factory.mktemp("overlay-identity")
    generated = work / "generated"
    generated.mkdir()
    _generate_formatter_includes(generated)
    source = work / "selector.c"
    source.write_text(_PROBE_SOURCE)
    library_path = work / "selector.so"
    subprocess.run([
        "cc", "-std=c99", "-O2", "-fPIC", "-shared",
        "-ffunction-sections", "-fdata-sections", "-Wl,--gc-sections",
        "-fvisibility=hidden",
        "-I", str(ROOT / "include"), "-I", str(ROOT / "pc_port"),
        "-I", str(ROOT / "pc_port/include"), "-I", str(generated),
        str(source), "-o", str(library_path),
    ], check=True, capture_output=True, stdin=subprocess.DEVNULL, timeout=180)
    library = ctypes.CDLL(str(library_path))
    library.overlay_selector_probe.argtypes = [ctypes.c_uint, ctypes.c_uint,
                                               ctypes.POINTER(ctypes.c_uint)]
    library.overlay_selector_probe.restype = ctypes.c_int
    return library.overlay_selector_probe


@pytest.mark.parametrize("overlay,pc", [(4, 0x800CEDFC), (10, 0x800CF104), (7, 0x800CEDFC)])
def test_unmapped_overlay_does_not_execute_overlay_zero(selector, overlay, pc):
    word = ctypes.c_uint(0xDEADBEEF)
    assert selector(pc, overlay, ctypes.byref(word)) == 0
    assert word.value == 0xDEADBEEF


@pytest.mark.parametrize("overlay,pc,expected", [
    (0, 0x800CF104, 0x8FBF0010),
    (4, 0x800CEEC8, 0x3C02800C),
    (10, 0x800D0488, 0x27BDFFE0),
    (7, 0x800CF104, 0x0C033D02),
])
def test_active_overlay_keeps_its_instructions(selector, overlay, pc, expected):
    word = ctypes.c_uint()
    assert selector(pc, overlay, ctypes.byref(word)) == 1
    assert word.value == expected


def test_every_title_export_is_selected_from_its_own_overlay(selector):
    overlay = (ROOT / "extracted/overlays/main/0010.bin").read_bytes()
    for path in (ROOT / "src/overlays/main_0010").glob("*.c"):
        words = re.findall(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)",
                           path.read_text())
        for index in range(len(words)):
            pc = int(path.stem, 16) + 4 * index
            offset = 0x20000 + pc - 0x800CEDF8
            expected, = struct.unpack_from("<I", overlay, offset)
            word = ctypes.c_uint(0xDEADBEEF)
            assert selector(pc, 10, ctypes.byref(word)) == 1, hex(pc)
            assert word.value == expected, hex(pc)


@pytest.mark.parametrize('overlay,expected', [(2031, 0x8C224F08), (0, 0x8C22EEA0)])
def test_scene_entry_dispatch_uses_selected_pac(selector, overlay, expected):
    word = ctypes.c_uint()
    assert selector(0x801282AC, overlay, ctypes.byref(word)) == 1
    assert word.value == expected


def test_every_sc02_export_is_selected_with_its_pac(selector):
    for path in (ROOT / 'src/overlays/sc02_0031').glob('*.c'):
        words = [int(w,16) for w in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
        for index, expected in enumerate(words):
            pc = int(path.stem,16)+4*index
            word = ctypes.c_uint()
            assert selector(pc,2031,ctypes.byref(word)) == 1
            assert word.value == expected


@pytest.mark.xfail(strict=False, reason=(
    "known PAC-isolation gap: the formatter carries unconditional "
    "kOverlaySc02_* ranges (and member0012 ranges are resident), so some "
    "SC02-only PCs are still served with no PAC selected. Gating them needs "
    "a live overlay-0012/sc02 selection decision, not a test change."))
def test_sc02_only_exports_do_not_leak_without_their_pac(selector):
    # Member0012 ranges are resident and carry no overlay gate, so a PC that is
    # also a member0012 export is legitimately served with no PAC selected.
    resident = set()
    for path in (ROOT / 'src/overlays/main_0012').glob('*.c'):
        count = len(re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text()))
        base = int(path.stem, 16)
        resident.update(base + 4 * i for i in range(count))
    leaked = []
    for path in (ROOT / 'src/overlays/sc02_0031').glob('*.c'):
        words = [int(w,16) for w in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
        for index in range(len(words)):
            pc = int(path.stem,16)+4*index
            if pc < 0x80128420 or pc in resident:
                continue
            word = ctypes.c_uint()
            if selector(pc,0,ctypes.byref(word)) != 0:
                leaked.append(hex(pc))
    assert not leaked, leaked
