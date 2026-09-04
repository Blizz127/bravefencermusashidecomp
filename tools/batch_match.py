#!/usr/bin/env python3
"""Try to match many functions at once, without ever destroying committed work.

For each function: decompile with m2c into a scratch directory, build it,
compare against retail through the oracle, and promote the source into `src/`
only if the oracle says MATCH. Anything less leaves no trace.

The safety rule is absolute and is the reason this file is written the way it
is. A previous batch wrote each candidate straight over its target path and
deleted the file when the build failed. `func_8012BF4C` already had a
hand-written, verified, committed source; the batch destroyed it, and nothing
noticed until the registry was re-verified afterwards. So:

* every intermediate lives in a scratch directory, never under `src/`;
* a target path that already exists is skipped before any work begins, and
  `promote` refuses it a second time at the moment of writing;
* nothing is ever deleted.

The expected outcome is that most functions do not match. m2c produces
plausible C, not the original C, and the gap between them is the whole problem.
A low promotion rate is the honest result, not a bug.
"""

from __future__ import annotations

import argparse
import contextlib
import io
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import build_candidate
import match_function
from retail_common import RetailError, load_json, write_json_atomic

CHILD_TIMEOUT_SECONDS = 120
GLABEL_RE = re.compile(r"^\s*glabel\s+(\S+)\s*$")
# /* fileofs vram bytes */  mnemonic ...
INSTRUCTION_RE = re.compile(r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")


@dataclass(frozen=True)
class FunctionRange:
    name: str
    vram: int
    size: int


@dataclass(frozen=True)
class Outcome:
    name: str
    status: str  # match | mismatch | build-failed | m2c-failed | skipped-existing

    @property
    def promoted(self) -> bool:
        return self.status == "match"


def enumerate_functions(text: str) -> list[FunctionRange]:
    """Every `glabel` in a splat disassembly, sized by its instruction words.

    Size comes from counting the instruction comments rather than subtracting
    the next label's address, so trailing padding between functions is not
    silently folded into the one before it.
    """

    found: list[FunctionRange] = []
    name: str | None = None
    vram: int | None = None
    words = 0

    def flush() -> None:
        nonlocal name, vram, words
        if name is not None and vram is not None and words > 0:
            found.append(FunctionRange(name=name, vram=vram, size=words * 4))
        name, vram, words = None, None, 0

    for line in text.splitlines():
        label = GLABEL_RE.match(line)
        if label:
            flush()
            name = label.group(1)
            continue
        if name is None:
            continue
        instruction = INSTRUCTION_RE.match(line)
        if instruction:
            if vram is None:
                vram = int(instruction.group(1), 16)
            words += 1
    flush()
    return found


def source_path(repo: Path, region: str, vram: int) -> Path:
    """Where a matched source for this function would live."""

    stem = f"{vram & 0xFFFFFFFF:08x}".lstrip("0") or "0"
    if region == "main":
        return repo / "src" / "main" / f"{stem}.c"
    return repo / "src" / "overlays" / region / f"{stem}.c"


def should_attempt(target: Path) -> bool:
    """False when a source already exists, so existing work is never touched."""

    return not target.exists()


def register(registry: dict[str, Any], registry_path: Path, entry: dict[str, Any]) -> None:
    """Append one match and persist immediately, so a kill loses at most one.

    The first version of this harness only wrote provenance/matches.json once,
    after the whole sweep finished. A kill mid-sweep — which happened twice
    running this over the largest overlay — left every already-promoted source
    on disk with no registry entry, needing hand recovery. Writing after each
    promotion means the file on disk is never behind what src/ actually holds.
    """

    key = (entry["name"], entry["region"])
    if any((m["name"], m["region"]) == key for m in registry["matches"]):
        return
    registry["matches"].append(entry)
    registry["matches"].sort(key=lambda m: (m["region"], m["vram"]))
    write_json_atomic(registry_path, registry)


def promote(produced: Path, target: Path) -> None:
    """Install a matched source, refusing to overwrite anything."""

    if target.exists():
        raise RetailError(
            f"refusing to overwrite an existing source: {target}. "
            "A batch destroyed committed work this way once; see docs/MATCHING.md."
        )
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(produced, target)


PROTO_RE = re.compile(r"^\?\s+(\w+)\((.*)\);(.*)$", re.MULTILINE)
LOCAL_VAR_RE = re.compile(r"^([ \t]+)\?\s+(\w+);\s*$", re.MULTILINE)
UNKNOWN_POINTER_RE = re.compile(r"\?\s*\*")
UNKNOWN_ARGS_RE = re.compile(r"\(\?\)")
FUNCPTR_RE = re.compile(r"\?\s*\(\*(\w+)\)\s*\([^;()]*\)")
EXTERN_UNKNOWN_RE = re.compile(r"^(\s*extern\s+)\?\s+(\w+\s*;)", re.MULTILINE)
BARE_PARAM_RE = re.compile(r"([(,]\s*)\?(?=\s*[,)])")
CALL_RE = re.compile(r"\b(\w+)\(")


def _sanitize(source: str) -> str:
    """Replace m2c's `?` placeholders with something the compiler accepts.

    m2c cannot see a symbol defined outside the functions it was asked to
    decompile, so it marks its type `?`, which is not valid C. `?` shows up in
    six shapes here, and they need different fixes:

    * A top-level `? NAME(...)` declaration is m2c's guess that the symbol is
      a function. That guess is wrong for a symbol that is only ever assigned
      to, never called — declaring it as a function and then assigning to it
      is not a valid lvalue. So the body decides: if `NAME(` appears anywhere
      in the function being compiled, it really is called, and the
      declaration becomes `void NAME(...)`. Otherwise it is external data and
      the declaration becomes `extern s32 NAME;`, a plain register-sized
      global. Register width is the only fact known about it.
    * `?` where a pointee type belongs (`? *`) becomes `void *`.
    * `(?)` as a whole parameter list — "arguments unchecked" — is the C89
      old-style declaration: empty parens, no `void` keyword. The call itself
      still passes whatever registers the assembly loaded.
    * A local `? name;` with no further type information becomes `s32 name;`,
      for the same register-sized-default reason as the data case above.
    * A function-pointer `? (*name)(...)` — local or parameter — becomes
      `s32 (*name)()`. The return type is unknowable and the call sequence
      is identical either way when the caller ignores `$v0`, while `s32`
      also compiles when the value is used. This runs before the `? *`
      rule, which would otherwise match the `? *` prefix and leave garbage.
    * `extern ? NAME;` becomes `extern s32 NAME;`, the same default as above.
    * A bare `?` parameter becomes `s32`. This runs after `(?)` → `()`
      so the C89 unchecked-args form keeps its empty-parens mapping.
    """

    # Called-ness is decided from the body only: the `?` declaration itself
    # is `NAME(...)`, so scanning the whole source would always find NAME
    # "called" right there in its own prototype.
    called = set(CALL_RE.findall(PROTO_RE.sub("", source)))

    def proto(match: "re.Match[str]") -> str:
        name, params, trailing = match.group(1), match.group(2), match.group(3)
        if name in called:
            params = FUNCPTR_RE.sub(r"s32 (*\1)()", params)
            params = UNKNOWN_POINTER_RE.sub("void *", params)
            return f"void {name}({params});{trailing}"
        return f"extern s32 {name};"

    source = FUNCPTR_RE.sub(r"s32 (*\1)()", source)
    source = PROTO_RE.sub(proto, source)
    source = LOCAL_VAR_RE.sub(lambda m: f"{m.group(1)}s32 {m.group(2)};", source)
    source = UNKNOWN_ARGS_RE.sub("()", source)
    source = UNKNOWN_POINTER_RE.sub("void *", source)
    source = EXTERN_UNKNOWN_RE.sub(r"\1s32 \2", source)
    source = BARE_PARAM_RE.sub(r"\1s32", source)
    return source


def run_m2c(m2c: Path, asm: Path, function: str, output: Path) -> bool:
    """Decompile one function. Every child gets a closed stdin and a timeout."""

    try:
        result = subprocess.run(
            [sys.executable, str(m2c), "-f", function, str(asm)],
            stdin=subprocess.DEVNULL,
            capture_output=True,
            text=True,
            timeout=CHILD_TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired:
        return False
    if result.returncode != 0 or not result.stdout.strip():
        return False
    output.write_text(
        '#include "psx_types.h"\n\n'
        f"/* Decompiled by m2c from {asm.name}, then verified byte-exact\n"
        " * against retail by tools/match_function.py. Types and signatures are\n"
        " * whatever reproduces the bytes; they are not evidence of the\n"
        " * original declaration. */\n\n" + _sanitize(result.stdout)
    )
    return True


def _quiet(fn, argv: list[str]) -> int:
    sink = io.StringIO()
    with contextlib.redirect_stdout(sink), contextlib.redirect_stderr(sink):
        return fn(argv)


def attempt(
    function: FunctionRange,
    region: str,
    target_spec: dict[str, Any],
    repo: Path,
    asm: Path,
    m2c: Path,
    scratch: Path,
) -> Outcome:
    """Decompile, build and compare one function. Promote only on MATCH."""

    target = source_path(repo, region, function.vram)
    if not should_attempt(target):
        return Outcome(function.name, "skipped-existing")

    produced = scratch / f"{function.name}.c"
    candidate = scratch / "candidate.bin"
    candidate.unlink(missing_ok=True)

    if not run_m2c(m2c, asm, function.name, produced):
        return Outcome(function.name, "m2c-failed")

    code = _quiet(
        build_candidate.main,
        [
            str(produced),
            "--symbol", function.name,
            "--link-base", f"0x{function.vram:X}",
            "--output", str(candidate),
        ],
    )
    if code != 0 or not candidate.is_file():
        return Outcome(function.name, "build-failed")

    match_argv = [
        "--vram", f"0x{function.vram:X}",
        "--size", f"0x{function.size:X}",
        "--candidate", str(candidate),
    ]
    if target_spec.get("kind") == "blob":
        match_argv += [
            "--retail-file", str(target_spec["file"]),
            "--base", f"0x{int(target_spec['base']):X}",
            "--sha256", str(target_spec["sha256"]),
        ]
    if _quiet(match_function.main, match_argv) != 0:
        return Outcome(function.name, "mismatch")

    promote(produced, target)
    return Outcome(function.name, "match")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asm", type=Path, required=True, help="splat disassembly, e.g. asm/main.s")
    parser.add_argument("--region", default="main", help="registry region name for these functions")
    parser.add_argument("--registry", type=Path, help="default: provenance/matches.json")
    parser.add_argument("--m2c", type=Path, help="default: tools/m2c/m2c.py")
    parser.add_argument("--limit", type=int, help="try at most this many functions")
    parser.add_argument("--max-size", type=int, default=256, help="skip functions larger than this many bytes")
    parser.add_argument("--dry-run", action="store_true", help="list what would be attempted and stop")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    repo = Path(__file__).resolve().parents[1]
    registry_path = args.registry or repo / "provenance/matches.json"
    m2c = args.m2c or repo / "tools/m2c/m2c.py"

    try:
        if not args.asm.is_file():
            raise RetailError(f"disassembly not found: {args.asm}; regenerate it with splat")
        if not m2c.is_file():
            raise RetailError(f"m2c not found: {m2c}")
        registry = load_json(registry_path)
        targets = registry.get("targets", {})
        if args.region not in targets:
            raise RetailError(f"region {args.region!r} is not a registered target in {registry_path}")
        target_spec = targets[args.region]

        functions = enumerate_functions(args.asm.read_text())
        pending = [
            f for f in functions
            if f.size <= args.max_size and should_attempt(source_path(repo, args.region, f.vram))
        ]
        if args.limit is not None:
            pending = pending[: args.limit]

        print(f"{len(functions)} functions in {args.asm}; {len(pending)} to attempt "
              f"(<= {args.max_size} bytes, no existing source)")
        if args.dry_run:
            for f in pending:
                print(f"  would attempt {f.name} at 0x{f.vram:08X}, {f.size} bytes")
            return 0

        outcomes: list[Outcome] = []
        promoted: list[FunctionRange] = []
        with tempfile.TemporaryDirectory(prefix="batch_match.") as scratch_dir:
            scratch = Path(scratch_dir)
            for index, function in enumerate(pending, 1):
                outcome = attempt(function, args.region, target_spec, repo, args.asm, m2c, scratch)
                outcomes.append(outcome)
                if outcome.promoted:
                    promoted.append(function)
                    register(
                        registry,
                        registry_path,
                        {
                            "name": function.name,
                            "vram": function.vram,
                            "size": function.size,
                            "region": args.region,
                            "source": str(source_path(repo, args.region, function.vram).relative_to(repo)),
                        },
                    )
                    print(f"  [{index}/{len(pending)}] MATCH {function.name} "
                          f"({function.size} bytes) -> {source_path(repo, args.region, function.vram)}")
                elif index % 25 == 0:
                    print(f"  [{index}/{len(pending)}] ...")

        tally: dict[str, int] = {}
        for outcome in outcomes:
            tally[outcome.status] = tally.get(outcome.status, 0) + 1
        print("\nRESULTS")
        for status in sorted(tally):
            print(f"  {status:<18}{tally[status]}")

        if promoted:
            print(f"\n{len(promoted)} new matches appended to {registry_path}")
            print("Re-verify with tools/verify_registry.py before committing.")
        return 0
    except RetailError as exc:
        print(f"batch_match: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
