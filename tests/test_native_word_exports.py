"""Compare exported instruction values, not just counts, with retail assembly."""
from pathlib import Path
import re

import pytest

ROOT = Path(__file__).resolve().parents[1]
WORD = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")
SOURCES = [p for p in sorted((ROOT / "src/main").glob("*.c"))
           if WORD.search(p.read_text())]
RETAIL = {int(address, 16): int.from_bytes(bytes.fromhex(raw), "little")
          for address, raw in re.findall(
              r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/",
              (ROOT / "asm/main.s").read_text())}


@pytest.mark.parametrize("source", SOURCES, ids=lambda p: p.name)
def test_export_matches_retail(source):
    actual = [int(word, 16) for word in WORD.findall(source.read_text())]
    if source.name == "8004239c_minus_one.c":
        # This export explicitly joins the entry path to its distant epilogue.
        addresses = list(range(0x8004239C, 0x80042400, 4))
        addresses += list(range(0x800424CC, 0x800424E4, 4))
    else:
        start = int(source.name[:8], 16)
        addresses = list(range(start, start + 4 * len(actual), 4))
    assert len(actual) == len(addresses)
    for address, word in zip(addresses, actual):
        assert word == RETAIL[address], f"{source.name}: mismatch at {address:08X}"


def test_800423cc_vsync_word_matches_pinned_exe_and_8004239c_export():
    """Live STOP 800423CC is the load-delay nop inside the existing VSync export."""
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    pc = 0x800423CC
    offset = pc - 0x80010000 + 0x800
    pinned = int.from_bytes(exe[offset:offset + 4], "little")
    source = (ROOT / "src/main/8004239c.c").read_text()
    actual = [int(word, 16) for word in WORD.findall(source)]
    index = (pc - 0x8004239C) // 4
    assert 0 <= index < len(actual)
    assert actual[index] == pinned == RETAIL[pc]


def test_8004248c_vsync_word_matches_pinned_exe_and_80042404_export():
    """Live STOP 8004248C is inside the existing [80042404,800424E4) VSync body."""
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    pc = 0x8004248C
    offset = pc - 0x80010000 + 0x800
    pinned = int.from_bytes(exe[offset:offset + 4], "little")
    source = (ROOT / "src/main/80042404.c").read_text()
    actual = [int(word, 16) for word in WORD.findall(source)]
    index = (pc - 0x80042404) // 4
    assert 0 <= index < len(actual)
    assert actual[index] == pinned == RETAIL[pc]


def test_8004256c_vsync_wait_word_matches_pinned_exe_and_800424e4_export():
    """Live STOP 8004256C is the wait-loop delay nop inside [800424E4,80042580)."""
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    pc = 0x8004256C
    offset = pc - 0x80010000 + 0x800
    pinned = int.from_bytes(exe[offset:offset + 4], "little")
    source = (ROOT / "src/main/800424e4.c").read_text()
    actual = [int(word, 16) for word in WORD.findall(source)]
    index = (pc - 0x800424E4) // 4
    assert 0 <= index < len(actual)
    assert actual[index] == pinned == RETAIL[pc] == 0


def test_80018f0c_epilogue_word_matches_pinned_exe_and_80018e9c_export():
    """Live STOP 80018F0C is the ra restore inside [80018E9C,80018F20)."""
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    pc = 0x80018F0C
    offset = pc - 0x80010000 + 0x800
    pinned = int.from_bytes(exe[offset:offset + 4], "little")
    source = (ROOT / "src/main/80018e9c.c").read_text()
    actual = [int(word, 16) for word in WORD.findall(source)]
    index = (pc - 0x80018E9C) // 4
    assert 0 <= index < len(actual)
    assert actual[index] == pinned == RETAIL[pc]


def test_packet_builder_complete_control_flow():
    import struct
    start, end = 0x800553F4, 0x80055D40
    words = [int(w,16) for w in WORD.findall((ROOT / 'src/main/800553f4.c').read_text())]
    assert len(words) == 595
    exe = (ROOT / 'extracted/disc/files/SLUS_007.26').read_bytes()
    table = struct.unpack_from('<30I',exe,0x80073C20-0x80010000+0x800)
    assert all(start <= target < end and target % 4 == 0 for target in table)
    calls = set()
    for index,word in enumerate(words):
        pc = start+4*index
        op = word >> 26
        if op in (2,3):
            target = ((pc+4)&0xF0000000) | ((word&0x03FFFFFF)<<2)
            if op == 3:
                calls.add(target)
            else:
                assert start <= target < end
        elif op in (1,4,5,6,7):
            offset = word & 0xFFFF
            if offset & 0x8000:
                offset -= 0x10000
            assert start <= pc+4+4*offset < end
    assert calls == {0x8005C604}
    assert words[-2:] == [0x03E00008,0]
