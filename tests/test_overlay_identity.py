"""Compile the production overlay selector; reject code from another overlay."""
import ctypes
from pathlib import Path
import re
import subprocess
import struct

import pytest

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


@pytest.fixture(scope="module")
def selector(tmp_path_factory):
    work = tmp_path_factory.mktemp("overlay-identity")
    source = (ROOT / "pc_port/mips_formatter.c").read_text()
    arrays = "\n".join(re.findall(
        r"static const uint32_t kOverlay\w+\[\] = \{.*?\};", source, re.S))

    def expand(match):
        name = match[1]
        local = ROOT / "pc_port" / name
        if local.exists():
            return local.read_text()
        title = re.fullmatch(r"([0-9a-f]+)_(sc01_0000|sc02_0031)_words.inc", name)
        if title:
            path = ROOT / f"src/overlays/{title[2]}/{title[1]}.c"
            return "\n".join(f"0x{word}," for word in re.findall(
                r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)", path.read_text()))
        parts = re.fullmatch(r"([0-9a-f]+)_overlay([0-9]+)_words.inc", name)
        assert parts, name
        path = ROOT / f"src/overlays/main_{parts[2]}/{parts[1]}.c"
        words = re.findall(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)",
                           path.read_text())
        assert words, path
        return "\n".join(f"0x{word}," for word in words)

    arrays = re.sub(r'#include "([^"]+)"', expand, arrays)
    start = source.index("    else if (g_overlay_0004_words &&\n")
    end = source.index("\nint musashi_boot_cpu_context", start)
    harness = (
        "#include <stdint.h>\n"
        "typedef struct { uint32_t pc; } Cpu;\n"
        "static int g_overlay_0004_words, g_overlay_0007_words, g_overlay_0010_words, g_overlay_sc02_0031_words;\n" + arrays +
        "\nint probe(unsigned pc, unsigned overlay, uint32_t *out) {\n"
        "Cpu state={pc}; Cpu *cpu=&state; uint32_t instruction;\n"
        "g_overlay_sc02_0031_words=overlay==2031; g_overlay_0004_words=overlay==4; g_overlay_0007_words=overlay==7; g_overlay_0010_words=overlay==10;\n"
        "if (0) return 0;\n" + source[start:end])
    path = work / "selector.c"
    path.write_text(harness)
    subprocess.run(["cc", "-shared", "-fPIC", str(path), "-o", str(work / "selector.so")],
                   check=True, capture_output=True, stdin=subprocess.DEVNULL, timeout=30)
    library = ctypes.CDLL(str(work / "selector.so"))
    library.probe.argtypes = [ctypes.c_uint, ctypes.c_uint,
                             ctypes.POINTER(ctypes.c_uint)]
    return library.probe


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


def test_every_sc02_export_requires_its_selected_pac(selector):
    for path in (ROOT / 'src/overlays/sc02_0031').glob('*.c'):
        words = [int(w,16) for w in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
        for index, expected in enumerate(words):
            pc = int(path.stem,16)+4*index
            word = ctypes.c_uint()
            assert selector(pc,2031,ctypes.byref(word)) == 1
            assert word.value == expected
            if pc >= 0x80128420:
                assert selector(pc,0,ctypes.byref(word)) == 0
