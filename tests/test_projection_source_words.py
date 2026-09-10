"""Compare bounded projection-source exports against asm and the pinned EXE."""
from pathlib import Path
import hashlib, json, os, re, struct
import pytest

ROOT = Path(__file__).resolve().parents[1]
WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")
EXPECTED = {
    "8005283c.c": (0x8005283C, 0x80052AA0, 153),
    "80052d00.c": (0x80052D00, 0x80052D90, 36),
    "80052bec.c": (0x80052BEC, 0x80052D00, 69),
}

def retail_words(exe, start, count):
    offset = start - 0x80010000 + 0x800
    raw = exe[offset:offset + count * 4]
    return [struct.unpack_from("<I", raw, i)[0] for i in range(0, len(raw), 4)]

def test_projection_exports_match_asm_and_pinned_exe():
    exe_path = ROOT / "extracted/disc/files/SLUS_007.26"
    asm_path = ROOT / "asm/main.s"
    if not exe_path.exists() or not asm_path.exists():
        pytest.skip("pinned retail inputs unavailable")
    exe = exe_path.read_bytes()
    assert hashlib.sha256(exe).hexdigest() == "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a"
    asm_words = {int(a, 16): int.from_bytes(bytes.fromhex(w), "little") for a, w in re.findall(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", asm_path.read_text())}
    manifest = json.loads((ROOT / "artifacts/projection-source-exports.json").read_text())
    assert manifest["status"] == "SOURCE_EXPORTS_PUBLISHED"
    assert manifest["c_match_claim"] is False
    assert manifest["licensed_payload_copied"] is False
    assert manifest["total_words"] == 258
    for name, (start, end, count) in EXPECTED.items():
        words = [int(w, 16) for w in WORD_RE.findall((ROOT / "src/main" / name).read_text())]
        assert len(words) == count
        assert words == [asm_words[start + i * 4] for i in range(count)]
        assert words == retail_words(exe, start, count)
        raw = b"".join(struct.pack("<I", w) for w in words)
        entry = next(x for x in manifest["exports"] if x["address"] == f"{start:08X}")
        assert entry["end"] == f"{end:08X}"
        assert entry["words"] == count
        assert entry["raw_sha256"] == hashlib.sha256(raw).hexdigest()
        assert entry["asm_match"] is True
        assert entry["pinned_exe_match"] is True
        assert entry["c_match_claim"] is False
