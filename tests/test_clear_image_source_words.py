"""Compare clear-image source exports against asm and the pinned EXE."""
from pathlib import Path
import hashlib, json, re, struct

ROOT = Path(__file__).resolve().parents[1]
WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")
EXPECTED = {
    "80059888.c": (0x80059888, 0x8005991C, 37),
    "80059760.c": (0x80059760, 0x80059888, 74),
    "8005af68.c": (0x8005AF68, 0x8005B1C4, 151),
}

def test_clear_image_exports_match_asm_and_pinned_exe():
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    assert hashlib.sha256(exe).hexdigest() == "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a"
    pairs = re.findall(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", (ROOT / "asm/main.s").read_text())
    asm_words = {int(a, 16): int.from_bytes(bytes.fromhex(w), "little") for a, w in pairs}
    manifest = json.loads((ROOT / "artifacts/clear-image-source-exports.json").read_text())
    assert manifest["status"] == "SOURCE_EXPORTS_PUBLISHED"
    assert manifest["total_words"] == 262
    assert manifest["total_executable_words"] == 262
    assert manifest["c_match_claim"] is False
    assert manifest["licensed_payload_copied"] is False
    for name, (start, end, count) in EXPECTED.items():
        words = [int(w, 16) for w in WORD_RE.findall((ROOT / "src/main" / name).read_text())]
        assert len(words) == count
        assert words == [asm_words[start + i * 4] for i in range(count)]
        raw = b"".join(struct.pack("<I", w) for w in words)
        offset = start - 0x80010000 + 0x800
        assert raw == exe[offset:offset + len(raw)]
        entry = next(x for x in manifest["exports"] if x["address"] == f"{start:08X}")
        assert entry["end"] == f"{end:08X}" and entry["words"] == count
        assert entry["executable_words"] == count
        assert entry["raw_sha256"] == hashlib.sha256(raw).hexdigest()
        assert entry["c_match_claim"] is False
