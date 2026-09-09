#!/usr/bin/env python3
"""Extract MUSASHI_NATIVE_MIPS_WORD(0x...) lines from a leaf .c into a .inc."""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(\s*(0x[0-9A-Fa-f]+)\s*\)")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--expected-words", type=int, required=True)
    args = parser.parse_args()

    text = args.source.read_text(encoding="utf-8", errors="replace")
    words = WORD_RE.findall(text)
    if len(words) != args.expected_words:
        print(
            f"{args.source}: expected {args.expected_words} words, found {len(words)}",
            file=sys.stderr,
        )
        return 1

    args.output.parent.mkdir(parents=True, exist_ok=True)
    body = ",\n".join(w.lower() for w in words) + ",\n"
    args.output.write_text(body, encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
