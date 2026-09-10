"""Verify published camera exports against the pinned EXE and asm."""
from pathlib import Path
import hashlib
import json
import re
import struct


ROOT = Path(__file__).resolve().parents[1]
WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-Fa-f]{8})\)")
EXPECTED = {
    "800144d4.c": (0x800144D4, 0x80014554, 32),
    "80053308.c": (0x80053308, 0x80053328, 8),
    "80053f6c.c": (0x80053F6C, 0x80054340, 245),
    "80053b20.c": (0x80053B20, 0x80053BD8, 46),
    "8004787c.c": (0x8004787C, 0x800478B8, 15),
    "800478b8.c": (0x800478B8, 0x80047948, 36),
    "80047948.c": (0x80047948, 0x800479E8, 40),
    "80054340.c": (0x80054340, 0x80054430, 60),
    "80054430.c": (0x80054430, 0x800544F8, 50),
    "800544f8.c": (0x800544F8, 0x80054514, 7),
    "80047d3c.c": (0x80047D3C, 0x80047DC0, 33),
}


def test_camera_exports_match_asm_and_pinned_exe():
    exe = (ROOT / "extracted/disc/files/SLUS_007.26").read_bytes()
    assert hashlib.sha256(exe).hexdigest() == (
        "66371c3a7517e9eabd7cb6cf0c5abffe7296bd4bac29c85b8bf7bb9db349714a"
    )
    asm_words = {
        int(address, 16): int.from_bytes(bytes.fromhex(word), "little")
        for address, word in re.findall(
            r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/",
            (ROOT / "asm/main.s").read_text(),
        )
    }
    manifest = json.loads(
        (ROOT / "artifacts/camera-source-exports.json").read_text()
    )
    assert manifest["status"] == "SOURCE_EXPORTS_PUBLISHED"
    assert manifest["total_words"] == sum(item[2] for item in EXPECTED.values()) == 572
    assert manifest["c_match_claim"] is False
    assert manifest["licensed_payload_copied"] is False
    for name, (start, end, count) in EXPECTED.items():
        source = (ROOT / "src/main" / name).read_text()
        words = [int(word, 16) for word in WORD_RE.findall(source)]
        assert len(words) == count
        assert words == [asm_words[start + index * 4] for index in range(count)]
        offset = start - 0x80010000 + 0x800
        raw = b"".join(struct.pack("<I", word) for word in words)
        assert raw == exe[offset:offset + len(raw)]
        entry = next(item for item in manifest["exports"]
                     if item["address"] == f"{start:08X}")
        assert entry["end"] == f"{end:08X}"
        assert entry["words"] == count
        assert entry["raw_sha256"] == hashlib.sha256(raw).hexdigest()
        assert entry["asm_match"] is True
        assert entry["pinned_exe_match"] is True
        assert entry["c_match_claim"] is False
        assert "MUSASHI_NATIVE_MIPS_WORD" not in source.split("#else\n", 1)[1]


def test_53308_else_body_preserved_by_publication():
    manifest = json.loads(
        (ROOT / "artifacts/camera-source-exports.json").read_text())
    entry = next(item for item in manifest["exports"]
                 if item["address"] == "80053308")
    source = (ROOT / "src/main/80053308.c").read_text()
    proposed_else = source.split("#else\n", 1)[1].removesuffix("#endif\n")
    assert entry["preserved_else_sha256"] == hashlib.sha256(
        proposed_else.encode()).hexdigest()
    assert entry["preserved_else_sha256"] == (
        "e58f1e5b00e9ac6062f2bd623e8b2f80e58804f2722586aa2d85e1ddf215444c"
    )

