#!/usr/bin/env python3
"""Re-decompile the unverified drafts that do not compile, and only those.

A draft that does not compile can never reach the oracle, so it is dead
weight: `batch_match.py --register-existing` reports `build-failed` and
moves on. Most of those failures had one cause. m2c, run in its default
mode, spells an access into an untyped global `NAME.unkHHHH`, while the
sanitizer has already had to declare NAME a plain scalar, so the retail
compiler rejects the member access. `--valid-syntax` emits the same access
as M2C_FIELD carrying the width m2c inferred, which compiles.

This tool is deliberately narrow, because the sources it edits are checked
work:

* A function already in the registry is never touched.
* A body that does not carry the UNVERIFIED draft marker is never touched.
  A verified match, a hand-written body, and an assembly overlay all stay
  exactly as they are.
* A draft that already compiles is never touched. Being close enough to
  build is progress; replacing it with a fresh guess would throw that away.
* The `MUSASHI_NATIVE_MIPS_WORD_EXPORT` block is copied across verbatim and
  compared word for word afterwards. Those words feed the native seam
  through tools/extract_asm_words.py, and a changed count fails the build.
* A regenerated body that still does not compile is discarded, leaving the
  original file on disk.

Nothing here claims a match. Every file it writes is still an unverified
draft; only tools/match_function.py can promote one.
"""

from __future__ import annotations

import argparse
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

import batch_match
import build_candidate
from retail_common import RetailError

REGIONS = {
    "main": "asm/main.s",
    "main_0007": "asm/overlays/main_0007/main_0007.s",
    "main_0012": "asm/overlays/main_0012/main_0012.s",
}

EXPORT_WORD_RE = re.compile(r"MUSASHI_NATIVE_MIPS_WORD\(0x([0-9a-fA-F]{8})\)")
DRAFT_MARKER = "UNVERIFIED draft"
IFDEF = "#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT"


def split_dual_shape(text: str) -> tuple[str, str] | None:
    """Return (export block, body) for a word-export/`#else` source.

    Returns None for any other shape, which is then left alone rather than
    guessed at.
    """

    if IFDEF not in text or "#else" not in text:
        return None
    head, rest = text.split(IFDEF, 1)
    if "#else" not in rest:
        return None
    export, body = rest.split("#else", 1)
    if not body.rstrip().endswith("#endif"):
        return None
    return head + IFDEF + export, body.rstrip()[: -len("#endif")]


def builds(source: Path, symbol: str, vram: int, scratch: Path) -> bool:
    """True when at least one candidate optimization produces bytes."""

    candidate = scratch / "probe.bin"
    for optimization in batch_match.OPTIMIZATION_CANDIDATES:
        candidate.unlink(missing_ok=True)
        code = batch_match._quiet(
            build_candidate.main,
            [
                str(source),
                "--symbol", symbol,
                "--link-base", f"0x{vram:X}",
                f"--optimization={optimization}",
                "--output", str(candidate),
            ],
        )
        if code == 0 and candidate.is_file():
            return True
    return False


def recarve_region(region: str, repo: Path, registered: set[int], limit: int | None,
                   dry_run: bool) -> dict[str, int]:
    asm = repo / REGIONS[region]
    text = asm.read_text()
    m2c = repo / "tools" / "m2c" / "m2c.py"
    counts: dict[str, int] = {}

    def bump(key: str) -> None:
        counts[key] = counts.get(key, 0) + 1

    attempted = 0
    with tempfile.TemporaryDirectory() as directory:
        scratch = Path(directory)
        for function in batch_match.enumerate_functions(text):
            if function.vram in registered:
                continue
            target = batch_match.source_path(repo, region, function.vram)
            if not target.is_file():
                bump("no-source")
                continue
            original = target.read_text()
            if DRAFT_MARKER not in original:
                bump("skipped-not-a-draft")
                continue
            parts = split_dual_shape(original)
            if parts is None:
                bump("skipped-shape")
                continue
            export, _ = parts
            if limit is not None and attempted >= limit:
                break
            attempted += 1
            if builds(target, function.name, function.vram, scratch):
                bump("skipped-already-builds")
                continue

            fresh = scratch / f"{function.name}.c"
            asm_copy = scratch / f"{function.name}.s"
            asm_copy.write_text(
                batch_match.m2c_assembly_text(text, function), encoding="utf-8"
            )
            if not batch_match.run_m2c(
                m2c, asm_copy, function.name, fresh, display_asm_name=asm.name
            ):
                bump("m2c-failed")
                continue

            rebuilt = (
                export
                + "#else\n"
                + fresh.read_text().strip()
                + "\n#endif\n"
            )
            if EXPORT_WORD_RE.findall(rebuilt) != EXPORT_WORD_RE.findall(original):
                raise RetailError(
                    f"refusing to write {target}: export words would change"
                )
            probe = scratch / f"probe_{function.name}.c"
            probe.write_text(rebuilt)
            if not builds(probe, function.name, function.vram, scratch):
                bump("still-build-failed")
                continue
            if dry_run:
                bump("would-rewrite")
                continue
            target.write_text(rebuilt)
            bump("rewritten")
    return counts


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--region", action="append", choices=sorted(REGIONS),
                        help="repeatable; default is every region")
    parser.add_argument("--registry", type=Path, default=Path("provenance/matches.json"))
    parser.add_argument("--limit", type=int, help="examine at most this many drafts per region")
    parser.add_argument("--dry-run", action="store_true")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    repo = Path(__file__).resolve().parent.parent
    registry = json.loads((repo / args.registry).read_text())
    for region in args.region or sorted(REGIONS):
        registered = {
            match["vram"] for match in registry["matches"] if match["region"] == region
        }
        counts = recarve_region(region, repo, registered, args.limit, args.dry_run)
        print(f"{region}:")
        for key in sorted(counts):
            print(f"  {key:26s} {counts[key]}")
    print("\nEvery rewritten file is still an UNVERIFIED draft. Run")
    print("tools/batch_match.py --register-existing to let the oracle judge them.")
    return 0


if __name__ == "__main__":
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    raise SystemExit(main())
