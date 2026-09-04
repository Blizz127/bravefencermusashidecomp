#!/usr/bin/env python3
"""Report decompilation progress in functions of real C.

Counted honestly, because the obvious metric lies. A project reporting its
`objdiff` match rate can show 100% while the "C" is verbatim `__asm__`
transcription; one PSX project publicly retracted exactly such a figure as
"true but meaningless". Only functions that rebuild from C and compare equal to
retail are counted here, and the registry records how to re-verify each.

The registry is provenance/matches.json. Nothing is added to it without the
oracle having reported MATCH.
"""

from __future__ import annotations

import argparse
import sys
from collections import Counter
from pathlib import Path
from typing import Any

from retail_common import RetailError, load_json

REQUIRED_FIELDS = ("name", "vram", "size", "source", "region")

# Two instructions or fewer: an empty stub, a single store, a plain return.
# These are genuine matches but are not meaningful progress, and a total that
# hides them behind a headline count invites exactly the inflation the
# rr-decomp retraction was about.
TRIVIAL_MAX_BYTES = 8


def load_registry(path: Path) -> list[dict[str, Any]]:
    """Read the match registry, refusing anything malformed."""

    if not path.is_file():
        raise RetailError(f"match registry not found: {path}")
    document = load_json(path)
    matches = document.get("matches")
    if not isinstance(matches, list):
        raise RetailError(f"registry {path} has no 'matches' list")
    return matches


def summarise(matches: list[dict[str, Any]]) -> dict[str, Any]:
    """Total the matched functions, refusing entries that would distort the count."""

    seen: set[int] = set()
    total_bytes = 0
    regions: Counter[str] = Counter()

    for match in matches:
        missing = [field for field in REQUIRED_FIELDS if field not in match]
        if missing:
            raise RetailError(
                f"match {match.get('name', '<unnamed>')!r} is missing {', '.join(missing)}"
            )
        size = match["size"]
        if not isinstance(size, int) or size <= 0:
            raise RetailError(f"match {match['name']!r} has a non-positive size: {size}")
        vram = match["vram"]
        if vram in seen:
            raise RetailError(f"match {match['name']!r} repeats vram 0x{vram:08X}")
        seen.add(vram)
        total_bytes += size
        regions[match["region"]] += 1

    trivial = sum(1 for m in matches if m["size"] <= TRIVIAL_MAX_BYTES)
    return {
        "function_count": len(matches),
        "matched_bytes": total_bytes,
        "by_region": dict(regions),
        "trivial_count": trivial,
        "substantive_count": len(matches) - trivial,
    }


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", type=Path, help="default: provenance/matches.json")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    repo = Path(__file__).resolve().parents[1]
    registry = args.registry or repo / "provenance/matches.json"
    try:
        matches = load_registry(registry)
        summary = summarise(matches)
        print(f"MATCHED {summary['function_count']} functions, {summary['matched_bytes']:,} bytes")
        for region, count in sorted(summary["by_region"].items()):
            region_bytes = sum(m["size"] for m in matches if m["region"] == region)
            print(f"  {region:<12} {count:>4} functions  {region_bytes:>8,} bytes")
        print()
        print(
            f"  of which trivial (<= {TRIVIAL_MAX_BYTES} bytes): "
            f"{summary['trivial_count']}    substantive: {summary['substantive_count']}"
        )
        print()
        print("Counted as functions rebuilt from C and verified equal to retail.")
        print("Not a diff percentage. A stub is a real match but not real progress;")
        print("see docs/MATCHING.md.")
        return 0
    except RetailError as exc:
        print(f"progress: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
