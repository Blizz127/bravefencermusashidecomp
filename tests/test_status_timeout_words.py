"""Keep the timeout slice identical to its tracked retail disassembly."""
from pathlib import Path
import re


def test_timeout_words_match_retail_disassembly():
    root = Path(__file__).resolve().parents[1]
    source = (root / "src/main/80044198_timeout_prefix.c").read_text()
    actual = [int(word, 16) for word in re.findall(
        r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9A-F]{8})\)", source)]
    expected = [int.from_bytes(bytes.fromhex(raw), "little")
                for address, raw in re.findall(
                    r"/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/",
                    (root / "asm/main.s").read_text())
                if 0x80044198 <= int(address, 16) < 0x800441D8]
    assert len(expected) == 16
    assert actual == expected
