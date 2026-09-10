"""Compare the published future continuation export against asm and retail."""
from pathlib import Path
import hashlib, json, re, struct

ROOT = Path(__file__).resolve().parents[1]
WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")

def test_future_projection_export_matches_asm_and_pinned_exe():
    exe_path = ROOT / "extracted/disc/files/SLUS_007.26"
    asm_path = ROOT / "asm/main.s"
    exe = exe_path.read_bytes()
    assert hashlib.sha256(exe).hexdigest() == "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a"
    pairs = re.findall(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/", asm_path.read_text())
    expected = [int.from_bytes(bytes.fromhex(w), "little") for a, w in pairs if 0x80053178 <= int(a, 16) < 0x80053218]
    source = [int(w, 16) for w in WORD_RE.findall((ROOT / "src/main/80053178.c").read_text())]
    assert len(source) == 40 and source == expected
    raw = b"".join(struct.pack("<I", w) for w in source)
    offset = 0x80053178 - 0x80010000 + 0x800
    assert raw == exe[offset:offset + len(raw)]
    manifest = json.loads((ROOT / "artifacts/projection-offset-source-exports.json").read_text())
    entry = manifest["exports"][0]
    assert manifest["status"] == "SOURCE_EXPORTS_PUBLISHED"
    assert manifest["total_words"] == 40
    assert entry["raw_sha256"] == hashlib.sha256(raw).hexdigest()
    assert entry["c_match_claim"] is False
    assert manifest["c_match_claim"] is False
    assert manifest["licensed_payload_copied"] is False
