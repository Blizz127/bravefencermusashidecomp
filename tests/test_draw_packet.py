"""Retail packet bytes and pure source construction; no GPU completion fixture."""
from pathlib import Path
import hashlib
import re
import struct
import subprocess
import tempfile
import pytest
from test_bios_event_callbacks import _generate_formatter_includes

ROOT = Path(__file__).resolve().parents[1]
RANGES = [(0x80059D68,0x80059E6C),(0x8005A870,0x8005AB00),
          (0x8005AB00,0x8005AB58),(0x8005AB58,0x8005AC24),
          (0x8005AC24,0x8005ACF0),(0x8005ACF0,0x8005AD34),
          (0x8005AD34,0x8005ADB8),(0x8005B7B0,0x8005BA90),
          (0x8005B710,0x8005B75C),(0x8005C020,0x8005C054),
          (0x800426FC,0x80042718)]


def pinned_exe():
    path = ROOT/'extracted/disc/files/SLUS_007.26'
    if not path.exists():
        pytest.skip('pinned licensed EXE unavailable')
    data = path.read_bytes()
    assert hashlib.sha256(data).hexdigest() == '66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a'
    return path, data


def test_draw_exports_match_exe_and_assembly():
    _, exe = pinned_exe()
    assembly = {int(pc,16):bytes.fromhex(raw) for pc,raw in re.findall(
        r'/\*\s+[0-9A-F]+\s+([0-9A-F]{8})\s+([0-9A-F]{8})\s+\*/',
        (ROOT/'asm/main.s').read_text())}
    for start,end in RANGES:
        text = (ROOT/f'src/main/{start:08x}.c').read_text()
        words = [int(x,16) for x in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)',text)]
        raw = struct.pack('<'+'I'*len(words),*words)
        assert len(raw) == end-start
        assert raw == exe[start-0x80010000+0x800:end-0x80010000+0x800]
        assert raw == b''.join(assembly[pc] for pc in range(start,end,4))
    # Generated queue stream is184 words, while only84 idle-path words map.
    assert (RANGES[7][1]-RANGES[7][0])//4 == 184


def test_draw_packet_source_and_dispatch_guards():
    exe,_ = pinned_exe()
    with tempfile.TemporaryDirectory(prefix='musashi-draw-packet-') as temp:
        generated = Path(temp)/'generated'; generated.mkdir()
        _generate_formatter_includes(generated)
        binary = Path(temp)/'probe'
        subprocess.run(['cc','-std=c99','-O2','-Wall','-Wextra','-Werror',
            '-Wno-parentheses','-ffunction-sections','-fdata-sections','-Wl,--gc-sections',
            '-I',str(ROOT/'include'),'-I',str(ROOT/'pc_port/include'),'-I',str(generated),
            str(ROOT/'tests/draw_packet_probe.c'),str(ROOT/'pc_port/boot_memory.c'),
            '-lcrypto','-o',str(binary)],check=True,timeout=40)
        subprocess.run([str(binary),str(exe)],check=True,timeout=15)
