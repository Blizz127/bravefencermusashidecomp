#!/usr/bin/env python3
"""Extract an inline-assembly .word stream into a C initializer.

The native MIPS seam consumes the same audited instruction words as the retail
overlay.  This intentionally has no retail-media input: the checked source is
the only input, and an unexpected source shape fails the build configuration.
"""
from __future__ import annotations

import argparse
import re
from pathlib import Path


WORD = re.compile(r'(?:"\.word 0x|MUSASHI_NATIVE_MIPS_WORD\(0x)([0-9a-fA-F]{8})(?:\\n"|\))')
EXPORT_WORD = re.compile(r'MUSASHI_NATIVE_MIPS_WORD\(0x([0-9a-fA-F]{8})\)')
ASM_LABEL = re.compile(r'^glabel ([A-Za-z0-9_]+)$', re.MULTILINE)
ASM_ENDLABEL = re.compile(r'^endlabel ([A-Za-z0-9_]+)$', re.MULTILINE)
ASM_WORD = re.compile(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/')


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--expected-words", type=int, required=True)
    parser.add_argument("--asm-label",
                        help="extract one glabel/endlabel range from tracked assembly")
    args = parser.parse_args()
    source = args.source.read_text()
    if args.asm_label:
        start = next((match.end() for match in ASM_LABEL.finditer(source)
                      if match.group(1) == args.asm_label), None)
        if start is None:
            raise SystemExit(f"{args.source}: missing glabel {args.asm_label}")
        end = next((match.start() for match in ASM_ENDLABEL.finditer(source, start)
                    if match.group(1) == args.asm_label), None)
        if end is None:
            raise SystemExit(f"{args.source}: missing endlabel {args.asm_label}")
        # main.s comments hold little-endian bytes; native instruction words
        # use architectural byte order, like the source export form.
        words = [raw[6:8] + raw[4:6] + raw[2:4] + raw[0:2]
                 for raw in ASM_WORD.findall(source[start:end])]
    else:
        words = EXPORT_WORD.findall(source) or WORD.findall(source)
    if len(words) != args.expected_words:
        raise SystemExit(
            f"{args.source}: expected {args.expected_words} .word instructions, found {len(words)}"
        )
    args.output.write_text("/* Generated from the audited overlay; do not edit. */\n" +
                           ",\n".join(f"0x{word.lower()}u" for word in words) + ",\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
