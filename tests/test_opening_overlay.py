"""Opening code comes from MAIN member4, preserved in source-loaded RAM."""
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]


def test_opening_exports_match_the_archive_member():
    archive = (ROOT / 'extracted/disc/files/MAIN.CD').read_bytes()
    sector, size = struct.unpack_from('<II', archive, 8 + 4 * 8)
    member = archive[sector*2048:sector*2048+size]
    assert member == (ROOT / 'extracted/overlays/main/0004.bin').read_bytes()
    for path in (ROOT / 'src/overlays/main_0004').glob('*.c'):
        words = re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())
        assert words
        raw = struct.pack(f'<{len(words)}I', *(int(w,16) for w in words))
        offset = 0x800 + int(path.stem,16) - 0x800CEDF8
        assert raw == member[offset:offset+len(raw)]
    # The EXE's actual jal target is an entry, not a branch in member7.
    assert struct.unpack_from('<I', member, 0x800+0xD0)[0] == 0x3C02800C
    demo = (ROOT / 'extracted/overlays/main/0007.bin').read_bytes()
    assert struct.unpack_from('<I', demo, 0xD0)[0] == 0x10400007


def test_idle_continuation_exports_complete_retail_function():
    """The observed idle dispatch must include CF300 through its return slot."""
    path = ROOT / 'src/overlays/main_0004/800cf300.c'
    words = [int(w, 16) for w in re.findall(
        r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
    assert len(words) == (0x800CF370 - 0x800CF300) // 4
    archive = (ROOT / 'extracted/disc/files/MAIN.CD').read_bytes()
    sector, _ = struct.unpack_from('<II', archive, 8 + 4 * 8)
    offset = sector * 2048 + 0x800 + 0x800CF300 - 0x800CEDF8
    assert struct.pack('<28I', *words) == archive[offset:offset + 112]
    assert [0x80000000 | ((w & 0x3FFFFFF) << 2)
            for w in words if w >> 26 == 3] == [0x800CF3E8, 0x80059888, 0x800118AC]
    assert words[-2:] == [0x03E00008, 0]


def test_post_fade_continuation_exports_complete_retail_function():
    path = ROOT / 'src/overlays/main_0004/800cf370.c'
    words = [int(w, 16) for w in re.findall(
        r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
    assert len(words) == (0x800CF3A4 - 0x800CF370) // 4
    assert [0x80000000 | ((w & 0x3FFFFFF) << 2)
            for w in words if w >> 26 == 3] == [0x800146B0, 0x800118AC]
    assert words[-2:] == [0x03E00008, 0]


def test_next_scene_continuation_exports_complete_retail_function():
    path = ROOT / 'src/overlays/main_0004/800cf3a4.c'
    words = [int(w, 16) for w in re.findall(
        r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
    assert len(words) == (0x800CF3E8 - 0x800CF3A4) // 4
    assert [0x80000000 | ((w & 0x3FFFFFF) << 2)
            for w in words if w >> 26 == 3] == [0x800183E0]
    assert words[-2:] == [0x03E00008, 0]


def test_post_opening_transition_includes_shared_epilogue():
    path = ROOT / 'src/main/80011380.c'
    words = [int(w, 16) for w in re.findall(
        r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
    assert len(words) == (0x80011680 - 0x80011380) // 4
    exe = (ROOT / 'extracted/disc/files/SLUS_007.26').read_bytes()
    assert struct.pack('<192I', *words) == exe[0x1B80:0x1E80]
    # The disassembly's separate 11664 label is this function's return path.
    assert words[-7:] == [0x03C0E821, 0x8FBF0020, 0x8FBE001C,
                          0x8FB00018, 0x27BD0028, 0x03E00008, 0]
    jumps = [0x80000000 | ((w & 0x3FFFFFF) << 2) for w in words if w >> 26 == 2]
    assert 0x80011664 in jumps
    assert all(0x80011380 <= address < 0x80011680 for address in jumps)
