"""Compare draw follow-up exports against asm and the pinned EXE."""
from pathlib import Path
import hashlib, json, re, struct

ROOT = Path(__file__).resolve().parents[1]
WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")
EXPECTED = {
    "80053218.c": (0x80053218, 0x80053290, 30),
    "80014774.c": (0x80014774, 0x800147B8, 17),
    "800147b8.c": (0x800147B8, 0x80014928, 92),
}

def test_draw_followup_exports_match_asm_and_pinned_exe():
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    assert hashlib.sha256(exe).hexdigest() == "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a"
    pairs = re.findall(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", (ROOT / "asm/main.s").read_text())
    asm_words = {int(a, 16): int.from_bytes(bytes.fromhex(w), "little") for a, w in pairs}
    manifest = json.loads((ROOT / "artifacts/draw-followup-source-exports.json").read_text())
    assert manifest["status"] == "SOURCE_EXPORTS_PUBLISHED"
    assert manifest["total_words"] == 139
    assert manifest["c_match_claim"] is False
    assert manifest["licensed_payload_copied"] is False
    for name, (start, end, count) in EXPECTED.items():
        source = (ROOT / "src/main" / name).read_text()
        words = [int(w, 16) for w in WORD_RE.findall(source)]
        assert len(words) == count
        assert words == [asm_words[start + i * 4] for i in range(count)]
        raw = b"".join(struct.pack("<I", w) for w in words)
        offset = start - 0x80010000 + 0x800
        assert raw == exe[offset:offset + len(raw)]
        entry = next(x for x in manifest["exports"] if x["address"] == f"{start:08X}")
        assert entry["end"] == f"{end:08X}" and entry["words"] == count
        assert entry["raw_sha256"] == hashlib.sha256(raw).hexdigest()
        assert entry["c_match_claim"] is False
    body = (ROOT / "src/main/80053218.c").read_text().split("#else\n", 1)[1]
    assert "void func_80053218(void)" in body and "MUSASHI_NATIVE_MIPS_WORD" not in body
