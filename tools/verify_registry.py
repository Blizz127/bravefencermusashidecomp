#!/usr/bin/env python3
"""Re-verify every function in provenance/matches.json through the oracle.

The registry is a claim: each entry says its source rebuilds to retail bytes.
This rebuilds and re-compares all of them, so the claim is re-earned rather
than remembered. It exists because a batch once destroyed a committed match and
nothing else noticed; see docs/MATCHING.md.

Exit 0 only when every entry still matches.
"""

from __future__ import annotations

import argparse
import contextlib
import io
import sys
import tempfile
from pathlib import Path
from typing import Any

import build_candidate
import match_function
from retail_common import RetailError, load_json


def plan(entry: dict[str, Any], targets: dict[str, Any], candidate: Path) -> tuple[list[str], list[str]]:
    """Argument vectors for the build and the comparison of one entry."""

    region = entry["region"]
    target = targets.get(region)
    if target is None:
        raise RetailError(f"{entry['name']}: region {region!r} is not a registered target")

    build = [
        str(entry["source"]),
        "--symbol", str(entry["name"]),
        "--link-base", f"0x{int(entry['vram']):X}",
        "--output", str(candidate),
    ]
    match = [
        "--vram", f"0x{int(entry['vram']):X}",
        "--size", f"0x{int(entry['size']):X}",
        "--candidate", str(candidate),
    ]
    kind = target.get("kind")
    if kind == "executable":
        pass
    elif kind == "blob":
        match += [
            "--retail-file", str(target["file"]),
            "--base", f"0x{int(target['base']):X}",
            "--sha256", str(target["sha256"]),
        ]
    else:
        raise RetailError(f"{entry['name']}: target kind {kind!r} is not understood")
    return build, match


def _quiet(fn, argv: list[str]) -> tuple[int, str]:
    sink = io.StringIO()
    with contextlib.redirect_stdout(sink), contextlib.redirect_stderr(sink):
        code = fn(argv)
    return code, sink.getvalue()


def verify_all(registry: Path, verbose: bool) -> int:
    data = load_json(registry)
    targets = data.get("targets", {})
    entries = data.get("matches", [])
    if not entries:
        raise RetailError(f"{registry} lists no matches")

    failures = 0
    with tempfile.TemporaryDirectory(prefix="verify_registry.") as scratch:
        for entry in entries:
            candidate = Path(scratch) / "candidate.bin"
            candidate.unlink(missing_ok=True)
            build_argv, match_argv = plan(entry, targets, candidate)
            code, out = _quiet(build_candidate.main, build_argv)
            if code != 0 or not candidate.is_file():
                failures += 1
                print(f"BUILD FAILED  {entry['name']}  ({entry['source']})")
                if verbose:
                    print(out)
                continue
            code, out = _quiet(match_function.main, match_argv)
            if code == 0:
                print(f"MATCH         {entry['name']}")
            else:
                failures += 1
                print(f"MISMATCH      {entry['name']}  ({entry['source']})")
                if verbose:
                    print(out)
    print(f"\n{len(entries) - failures}/{len(entries)} registry entries re-verified")
    return failures


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", type=Path, help="default: provenance/matches.json")
    parser.add_argument("--verbose", action="store_true", help="print tool output on failure")
    args = parser.parse_args(argv)
    repo = Path(__file__).resolve().parents[1]
    registry = args.registry or repo / "provenance/matches.json"
    try:
        return 1 if verify_all(registry, args.verbose) else 0
    except RetailError as exc:
        print(f"verify_registry: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
