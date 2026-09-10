#!/usr/bin/env python3
"""Report registered byte ranges and explicit source-recovery classifications.

The registry can contain C, assembly, and partial ranges. A .c filename and an
exact byte match do not establish complete C recovery. Missing classifications
remain unclassified. This report reads claims; verify_registry.py re-earns the
byte comparisons. See docs/PROGRESS.md for classification requirements.
"""

from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from pathlib import Path
from typing import Any

from retail_common import RetailError, load_json

REQUIRED_FIELDS = ("name", "vram", "size", "source", "region")
RECOVERY_KINDS = ("c", "assembly", "mixed", "unclassified")
EXTENTS = ("function", "partial", "unclassified")
QUALIFYING_RECOVERIES = frozenset({"c", "assembly"})

# Identified split code: SLUS_007.26 t_size + MAIN.CD member 0007 + member
# 0012's code chunk [0x28000, 0x86000). Overlay members not yet shown to be
# code are outside this denominator.
IDENTIFIED_REGION_BYTES = {
    "main": 411648,
    "main_0007": 9600,
    "main_0012": 385024,
}
IDENTIFIED_CODE_BYTES = sum(IDENTIFIED_REGION_BYTES.values())
# ceil(30% of 806272) = 241882 unique qualifying bytes.
COVERAGE_THRESHOLD_BYTES = (IDENTIFIED_CODE_BYTES * 3 + 9) // 10

# Two instructions or fewer: an empty stub, a single store, a plain return.
# These are genuine matches but are not meaningful progress, and a total that
# hides them behind a headline count invites exactly the inflation the
# rr-decomp retraction was about.
TRIVIAL_MAX_BYTES = 8


_COMMENT_RE = re.compile(r"/\*.*?\*/|//.*?$", re.S | re.M)
_NATIVE_IFELSE_RE = re.compile(
    r"#\s*if(?:n?def)?\s+MUSASHI_NATIVE_MIPS_WORD_EXPORT\b.*?"
    r"#\s*else\b(.*?)"
    r"#\s*endif",
    re.S,
)
_NATIVE_IF_RE = re.compile(
    r"#\s*if(?:n?def)?\s+MUSASHI_NATIVE_MIPS_WORD_EXPORT\b.*?#\s*endif",
    re.S,
)
_NATIVE_MACRO_RE = re.compile(r"^\s*MUSASHI_NATIVE_MIPS_WORD\s*\(.*$", re.M)
_ASM_BLOCK_RE = re.compile(
    r"(?:__asm__|asm)\s*(?:volatile)?\s*\(\s*(?P<payload>.*?)\)\s*;",
    re.S,
)
_STRING_LIT_RE = re.compile(r'"(?:\\.|[^"\\])*"')


def _asm_template(payload: str) -> str:
    """GNU asm template strings; ignore operand colons inside those strings."""

    in_str = False
    escape = False
    for index, char in enumerate(payload):
        if in_str:
            if escape:
                escape = False
            elif char == "\\":
                escape = True
            elif char == '"':
                in_str = False
        elif char == '"':
            in_str = True
        elif char == ":":
            return payload[:index]
    return payload


def classify_recovery(source: str) -> str:
    """Classify the PS1 implementation in source text.

    Native word-export macros are ignored: they are not the compiled
    implementation. Empty register constraints emit no instructions and stay
    C. Instruction `__asm__` overlays without a C body are assembly; a C body
    plus instruction asm is mixed. Verbatim `.word 0x...` dumps are
    unclassified transcription, not decompilation.
    """

    text = _COMMENT_RE.sub("", source)
    # Keep the `#else` C body; drop native-export-only `#ifdef` blocks.
    text = _NATIVE_IFELSE_RE.sub(r"\1", text)
    text = _NATIVE_IF_RE.sub("", text)
    text = _NATIVE_MACRO_RE.sub("", text)
    instruction_asm = False
    word_dump = False
    for block in _ASM_BLOCK_RE.finditer(text):
        # Only the template strings before the first operand colon count.
        # Constraint strings (`"=r"`) are not instructions. Label colons
        # inside the template must not cut the template short.
        header = _asm_template(block.group("payload"))
        literals = "".join(
            bytes(piece, "utf-8").decode("unicode_escape")[1:-1]
            for piece in _STRING_LIT_RE.findall(header)
        )
        if not literals.strip():
            continue
        directives = 0
        mnemonics = 0
        for stmt in literals.replace("\\n", "\n").splitlines():
            stmt = stmt.strip()
            if not stmt or stmt.startswith("#"):
                continue
            if stmt.startswith(".word"):
                directives += 1
            elif stmt.startswith(".") or stmt.endswith(":"):
                continue
            else:
                mnemonics += 1
        if directives and directives >= mnemonics:
            word_dump = True
        elif mnemonics or directives:
            instruction_asm = True
    without_asm = _ASM_BLOCK_RE.sub("", text)
    has_c = "{" in without_asm
    if word_dump and not instruction_asm:
        # Verbatim retail-word transcription is not decompilation.
        return "unclassified"
    if instruction_asm and has_c:
        return "mixed"
    if instruction_asm:
        return "assembly"
    if has_c:
        return "c"
    return "unclassified"


def _qualifies(match: dict[str, Any]) -> bool:
    """Complete reviewed C or assembly functions only; mixed/partial/unclassified do not count."""

    recovery = match.get("recovery", "unclassified")
    extent = match.get("extent", "unclassified")
    return recovery in QUALIFYING_RECOVERIES and extent == "function"


def unique_qualifying_bytes(matches: list[dict[str, Any]]) -> int:
    """Union overlapping vram spans per region; overlapping ranges count once."""

    spans: dict[str, list[tuple[int, int]]] = {}
    for match in matches:
        if not _qualifies(match):
            continue
        start = match["vram"]
        end = start + match["size"]
        spans.setdefault(match["region"], []).append((start, end))

    total = 0
    for intervals in spans.values():
        intervals.sort()
        merged_start, merged_end = intervals[0]
        for start, end in intervals[1:]:
            if start <= merged_end:
                merged_end = max(merged_end, end)
            else:
                total += merged_end - merged_start
                merged_start, merged_end = start, end
        total += merged_end - merged_start
    return total


def qualifying_coverage(
    matches: list[dict[str, Any]],
    identified_bytes: int = IDENTIFIED_CODE_BYTES,
) -> dict[str, Any]:
    """Unique qualifying coverage against the identified-code denominator."""

    unique = unique_qualifying_bytes(matches)
    return {
        "unique_qualifying_bytes": unique,
        "identified_bytes": identified_bytes,
        "meets_threshold": unique >= COVERAGE_THRESHOLD_BYTES,
    }


def fill_missing_classifications(
    matches: list[dict[str, Any]],
    *,
    read_source,
    complete_functions: set[tuple[str, int, int]],
) -> int:
    """Fill missing recovery/extent from source text and splat completeness.

    Already-reviewed labels are never overwritten. Native-export-only files
    stay unclassified. A range is a complete function only when splat
    enumerated the same region/vram/size.
    """

    filled = 0
    for match in matches:
        if "recovery" not in match:
            match["recovery"] = classify_recovery(read_source(match["source"]))
            filled += 1
        if "extent" not in match:
            key = (match["region"], match["vram"], match["size"])
            match["extent"] = "function" if key in complete_functions else "unclassified"
            filled += 1
    return filled


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
    """Total registered ranges and declared recovery, without inferring either."""

    seen: set[int] = set()
    total_bytes = 0
    regions: Counter[str] = Counter()
    recovery_counts: Counter[str] = Counter()
    recovery_bytes: Counter[str] = Counter()
    extents: Counter[str] = Counter()

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
        recovery = match.get("recovery", "unclassified")
        extent = match.get("extent", "unclassified")
        if recovery not in RECOVERY_KINDS or extent not in EXTENTS:
            raise RetailError(f"match {match['name']!r} has invalid recovery/extent classification")
        recovery_counts[recovery] += 1
        recovery_bytes[recovery] += size
        extents[extent] += 1

    trivial = sum(1 for m in matches if m["size"] <= TRIVIAL_MAX_BYTES)
    coverage = qualifying_coverage(matches)
    return {
        # Historical keys retained for callers; these count ranges, not proven
        # functions, and the size threshold does not imply substantive recovery.
        "function_count": len(matches),
        "matched_bytes": total_bytes,
        "by_region": dict(regions),
        "trivial_count": trivial,
        "substantive_count": len(matches) - trivial,
        "by_recovery": dict(recovery_counts),
        "bytes_by_recovery": dict(recovery_bytes),
        "by_extent": dict(extents),
        "unique_qualifying_bytes": coverage["unique_qualifying_bytes"],
        "identified_bytes": coverage["identified_bytes"],
        "meets_coverage_threshold": coverage["meets_threshold"],
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
        print(f"REGISTERED {summary['function_count']} ranges, {summary['matched_bytes']:,} summed bytes")
        for region, count in sorted(summary["by_region"].items()):
            region_bytes = sum(m["size"] for m in matches if m["region"] == region)
            print(f"  {region:<12} {count:>4} ranges  {region_bytes:>8,} bytes")
        print()
        print(
            f"  size <= {TRIVIAL_MAX_BYTES} bytes: {summary['trivial_count']}"
            f"    larger ranges: {summary['substantive_count']}"
        )
        print()
        print("Declared source recovery (not inferred from filenames):")
        for kind, count in sorted(summary["by_recovery"].items()):
            print(f"  {kind:<12} {count:>4} ranges  {summary['bytes_by_recovery'][kind]:>8,} bytes")
        print("Declared extent:")
        for extent, count in sorted(summary["by_extent"].items()):
            print(f"  {extent:<12} {count:>4} ranges")
        print()
        unique = summary["unique_qualifying_bytes"]
        identified = summary["identified_bytes"]
        percent = (100.0 * unique / identified) if identified else 0.0
        print(
            "Qualifying unique coverage (complete C/assembly functions, "
            "overlap-unioned per region):"
        )
        print(
            f"  {unique:,} / {identified:,} bytes "
            f"({percent:.2f}%)"
        )
        print(
            f"  30% threshold: {COVERAGE_THRESHOLD_BYTES:,} bytes"
            f"    {'MET' if summary['meets_coverage_threshold'] else 'NOT MET'}"
        )
        print()
        print("Registry claims only; run tools/verify_registry.py for fresh byte verification.")
        print("Summed ranges are not unique coverage or a full-decompilation percentage.")
        print("Classification is a reviewed claim, not proof of native execution or menu boot.")
        return 0
    except RetailError as exc:
        print(f"progress: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
