"""Retail SC02 member31 identity, including exhaustive wrong-word controls."""
import ctypes
import hashlib
from pathlib import Path
import re
import struct
import subprocess

from tools.decode_title_pac import decode

ROOT = Path(__file__).resolve().parents[1]


def test_sc02_entry_identity(tmp_path):
    archive = (ROOT / 'extracted/disc/files/SC02.CD').read_bytes()
    assert hashlib.sha256(archive).hexdigest() == '8a04737374845155390268f7269c1599ecf6b6669357089059b20f1dcad11607'
    sector, size = struct.unpack_from('<II', archive, 8 + 31*8)
    assert (sector*2048, size) == (15247360, 1050624)
    member = archive[sector*2048:sector*2048+size]
    assert struct.unpack_from('<4I', member) == (0x434150, 4, 0, 329157)
    code, consumed = decode(member[0x800:329157])
    assert consumed == 327109
    assert hashlib.sha256(code).hexdigest() == '5bb5b6364206ccd0c47d6cf6a1dc2627e13bbef3cda40d618103b92ccfef4db6'
    source = (ROOT / 'src/overlays/sc02_0031/80128158.c').read_text()
    words = [int(w,16) for w in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', source)]
    for path in (ROOT / 'src/overlays/sc02_0031').glob('*.c'):
        exported = [int(w,16) for w in re.findall(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)', path.read_text())]
        assert exported
        raw = struct.pack('<' + 'I'*len(exported), *exported)
        offset = int(path.stem,16)-0x80128158
        assert code[offset:offset+len(raw)] == raw, path.name
    assert len(words) == 178
    assert struct.pack('<178I', *words) == code[:712]
    assert words[(0x801282AC-0x80128158)//4] == 0x8C224F08
    formatter = (ROOT / 'pc_port/mips_formatter.c').read_text()
    helper = formatter[formatter.index('static int sc02_entry_matches('):formatter.index('static int formatter_step(')]
    harness = '''#include <stdint.h>
typedef struct { uint32_t words[178]; int fail; } MusashiBootMemory;
static const uint32_t kOverlaySc02_80128158Words[] = {''' + ','.join(map(str,words)) + '''};
static int musashi_boot_read32(MusashiBootMemory *m,uint32_t a,uint32_t *out) {
unsigned i=(a-0x80128158u)/4u;
if(i>=178 || (int)i==m->fail) return 0;
*out=m->words[i]; return 1;
}
''' + helper + '\nint probe(MusashiBootMemory *m) { return sc02_entry_matches(m); }\n'
    path = tmp_path / 'probe.c'; path.write_text(harness)
    lib = tmp_path / 'probe.so'
    subprocess.run(['cc','-shared','-fPIC',str(path),'-o',str(lib)],check=True,capture_output=True)
    class Memory(ctypes.Structure):
        _fields_ = [('words',ctypes.c_uint32*178),('fail',ctypes.c_int)]
    probe = ctypes.CDLL(str(lib)).probe
    probe.argtypes = [ctypes.POINTER(Memory)]
    memory = Memory((ctypes.c_uint32*178)(*words),-1)
    assert probe(ctypes.byref(memory)) == 1
    for i in range(178):
        memory.words[i] ^= 1
        assert probe(ctypes.byref(memory)) == 0
        memory.words[i] ^= 1
        memory.fail = i
        assert probe(ctypes.byref(memory)) == 0
        memory.fail = -1
    assert 'g_overlay_sc02_0031_words = sc02_entry_matches(memory);' in formatter
