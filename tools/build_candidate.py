#!/usr/bin/env python3
"""Compile one C file with a pinned Psy-Q toolchain and extract a function's bytes.

This produces candidates for match_function.py to judge. It does not decide
anything itself: a successful compile is not evidence of anything, and the
output is only meaningful once the oracle compares it with retail.

The compiler is driven the way the Psy-Q chain drove it, not the way a modern
gcc driver would: cpp and cc1 are invoked separately, then maspsx reproduces
ASPSX macro expansion before GNU as assembles the result. The ASPSX version is
tied to the compiler rather than passed in loosely, because the wrong expansion
silently prevents a match instead of failing loudly.
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

from retail_common import RetailError

WORD_SIZE = 4
DEFAULT_TOOLCHAIN_ROOT_ENV = "PSYQ_TOOLCHAIN_ROOT"

# maspsx selects its input source with sys.stdin.isatty() and calls
# sys.stdin.readlines() when stdin is not a tty. Every child therefore gets an
# explicit closed stdin: inheriting it would make this harness work
# interactively and hang under CI. The timeout turns any future hang into a
# loud failure instead of a stalled build.
CHILD_TIMEOUT_SECONDS = 120


@dataclass(frozen=True)
class Toolchain:
    name: str
    aspsx_version: str


# PSY-Q release -> compiler -> ASPSX assembler version.
TOOLCHAINS: dict[str, Toolchain] = {
    "gcc-2.6.0-psx": Toolchain("gcc-2.6.0-psx", "2.34"),
    "gcc-2.7.2-psx": Toolchain("gcc-2.7.2-psx", "2.56"),
    "gcc-2.7.2-cdk-psx": Toolchain("gcc-2.7.2-cdk-psx", "2.67"),
    "gcc-2.8.0-psx": Toolchain("gcc-2.8.0-psx", "2.77"),
    "gcc-2.8.1-psx": Toolchain("gcc-2.8.1-psx", "2.79"),
    "gcc-2.91.66-psx": Toolchain("gcc-2.91.66-psx", "2.81"),
}

TEXT_SYMBOL_TYPES = frozenset("Tt")


def resolve_toolchain(name: str) -> Toolchain:
    toolchain = TOOLCHAINS.get(name)
    if toolchain is None:
        available = ", ".join(sorted(TOOLCHAINS))
        raise RetailError(f"unknown toolchain {name!r}; available: {available}")
    return toolchain


def parse_nm_symbols(output: str) -> dict[str, tuple[int, int | None]]:
    """Map text symbol names to (section offset, size) from `nm -S` output.

    Only text symbols are kept, since a function's bytes live in .text. Symbols
    without a recorded size are reported as unsized rather than guessed at.
    """

    symbols: dict[str, tuple[int, int | None]] = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) == 4:
            value, size, kind, name = fields
        elif len(fields) == 3:
            value, kind, name = fields
            size = None
        else:
            continue
        if kind not in TEXT_SYMBOL_TYPES:
            continue
        try:
            offset = int(value, 16)
            length = int(size, 16) if size is not None else None
        except ValueError:
            continue
        symbols[name] = (offset, length)
    return symbols


def slice_symbol(section: bytes, offset: int, size: int) -> bytes:
    """Cut a symbol's bytes out of a section image."""

    if size <= 0:
        raise RetailError(f"symbol size must be positive, got {size}")
    if size % WORD_SIZE:
        raise RetailError(f"symbol size {size} is not a multiple of {WORD_SIZE}")
    if offset % WORD_SIZE:
        raise RetailError(f"symbol offset {offset} is not word-aligned")
    if offset + size > len(section):
        raise RetailError(
            f"symbol range {offset}+{size} overruns the {len(section)}-byte section"
        )
    return section[offset : offset + size]


def cpp_command(cpp: Path, source: Path, includes: list[Path] | None = None) -> list[str]:
    command = [
        str(cpp),
        "-undef",
        "-D__GNUC__=2",
        "-D__OPTIMIZE__",
        "-Dmips",
        "-D__mips__",
        "-D__LITTLE_ENDIAN__",
        "-D_LANGUAGE_C",
        "-nostdinc",
    ]
    for include in includes or []:
        command.append(f"-I{include}")
    command.append(str(source))
    return command


def cc1_command(
    cc1: Path, preprocessed: Path, output: Path, *, optimization: str = "-O2", gp: str = "-G0"
) -> list[str]:
    return [
        str(cc1),
        optimization,
        gp,
        "-mips1",
        "-mcpu=3000",
        "-w",
        "-funsigned-char",
        "-fpeephole",
        "-ffunction-cse",
        "-fpcc-struct-return",
        "-fcommon",
        "-msoft-float",
        "-mgas",
        "-fgnu-linker",
        "-quiet",
        str(preprocessed),
        "-o",
        str(output),
    ]


def maspsx_command(
    maspsx: Path,
    assembly: Path,
    obj: Path,
    *,
    aspsx_version: str,
    gnu_as: Path,
    gp: str = "-G0",
    expand_div: bool = True,
) -> list[str]:
    """Build the maspsx invocation.

    Division expansion defaults on because retail requires it: all 69 division
    sites in the executable carry the bnez/nop/break divide-by-zero guard, and
    no candidate toolchain emits that guard without --expand-div. See
    docs/MATCHING.md.
    """

    command = [
        sys.executable,
        str(maspsx),
        f"--aspsx-version={aspsx_version}",
        "--use-comm-section",
        "--run-assembler",
        f"--gnu-as-path={gnu_as}",
    ]
    if expand_div:
        command.append("--expand-div")
    command += [
        "-EL",
        gp,
        "-march=r3000",
        "-mtune=r3000",
        "-no-pad-sections",
        "-o",
        str(obj),
        str(assembly),
    ]
    return command


def _run(command: list[str], label: str, *, stdout: Path | None = None) -> None:
    try:
        if stdout is not None:
            with stdout.open("wb") as stream:
                completed = subprocess.run(
                    command,
                    check=False,
                    stdout=stream,
                    stderr=subprocess.PIPE,
                    stdin=subprocess.DEVNULL,
                    timeout=CHILD_TIMEOUT_SECONDS,
                )
        else:
            completed = subprocess.run(
                command,
                check=False,
                capture_output=True,
                stdin=subprocess.DEVNULL,
                timeout=CHILD_TIMEOUT_SECONDS,
            )
    except subprocess.TimeoutExpired as exc:
        raise RetailError(f"{label} timed out after {CHILD_TIMEOUT_SECONDS}s") from exc
    except OSError as exc:
        raise RetailError(f"failed to execute {label}: {exc}") from exc
    if completed.returncode != 0:
        detail = (completed.stderr or b"").decode("utf-8", errors="replace").strip()
        raise RetailError(f"{label} failed with exit code {completed.returncode}: {detail}")


def _capture(command: list[str], label: str) -> str:
    try:
        completed = subprocess.run(
            command,
            check=False,
            capture_output=True,
            text=True,
            errors="replace",
            stdin=subprocess.DEVNULL,
            timeout=CHILD_TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired as exc:
        raise RetailError(f"{label} timed out after {CHILD_TIMEOUT_SECONDS}s") from exc
    except OSError as exc:
        raise RetailError(f"failed to execute {label}: {exc}") from exc
    if completed.returncode != 0:
        raise RetailError(f"{label} failed with exit code {completed.returncode}: {completed.stderr.strip()}")
    return completed.stdout


def _require(path: Path, what: str) -> Path:
    if not path.is_file():
        raise RetailError(f"{what} not found: {path}")
    return path


def _resolve_binutil(name: str) -> Path:
    found = shutil.which(name)
    if found is None:
        raise RetailError(f"required binutil {name!r} was not found on PATH")
    return Path(found)


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="C file to compile")
    parser.add_argument("--symbol", required=True, help="function symbol to extract")
    parser.add_argument("--toolchain", default="gcc-2.7.2-psx", help="pinned Psy-Q toolchain name")
    parser.add_argument(
        "--toolchain-root",
        type=Path,
        help=f"directory holding toolchain subdirectories (or ${DEFAULT_TOOLCHAIN_ROOT_ENV})",
    )
    parser.add_argument("--maspsx", type=Path, help="path to maspsx.py")
    parser.add_argument("--output", type=Path, required=True, help="where to write the extracted bytes")
    parser.add_argument("--optimization", default="-O2")
    parser.add_argument("--gp", default="-G0")
    parser.add_argument("--include", type=Path, action="append", default=[])
    parser.add_argument("--keep-intermediates", action="store_true")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = build_parser().parse_args(argv)
    try:
        toolchain = resolve_toolchain(args.toolchain)
        root = args.toolchain_root or Path(os.environ.get(DEFAULT_TOOLCHAIN_ROOT_ENV, "tools/psyq"))
        toolchain_dir = Path(root).expanduser() / toolchain.name
        cpp = _require(toolchain_dir / "cpp", "cpp")
        cc1 = _require(toolchain_dir / "cc1", "cc1")
        maspsx = _require(
            args.maspsx or Path(root).expanduser().parent / "maspsx" / "maspsx.py", "maspsx.py"
        )
        gnu_as = _resolve_binutil("mips-linux-gnu-as")
        nm = _resolve_binutil("mips-linux-gnu-nm")
        objcopy = _resolve_binutil("mips-linux-gnu-objcopy")
        source = _require(args.source, "source")

        workspace = Path(tempfile.mkdtemp(prefix="candidate."))
        try:
            preprocessed = workspace / "unit.i"
            assembly = workspace / "unit.s"
            obj = workspace / "unit.o"
            text = workspace / "unit.text.bin"

            _run(cpp_command(cpp, source, args.include), "cpp", stdout=preprocessed)
            _run(
                cc1_command(cc1, preprocessed, assembly, optimization=args.optimization, gp=args.gp),
                "cc1",
            )
            _run(
                maspsx_command(
                    maspsx,
                    assembly,
                    obj,
                    aspsx_version=toolchain.aspsx_version,
                    gnu_as=gnu_as,
                    gp=args.gp,
                ),
                "maspsx",
            )

            symbols = parse_nm_symbols(_capture([str(nm), "-S", str(obj)], "nm"))
            if args.symbol not in symbols:
                known = ", ".join(sorted(symbols)) or "(none)"
                raise RetailError(f"symbol {args.symbol!r} not found in {obj.name}; text symbols: {known}")
            offset, size = symbols[args.symbol]
            if size is None:
                raise RetailError(
                    f"symbol {args.symbol!r} has no recorded size; cannot bound its bytes"
                )

            _run(
                [str(objcopy), "-O", "binary", "--only-section=.text", str(obj), str(text)],
                "objcopy",
            )
            extracted = slice_symbol(text.read_bytes(), offset, size)
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_bytes(extracted)

            print(
                f"CANDIDATE symbol={args.symbol} toolchain={toolchain.name} "
                f"aspsx={toolchain.aspsx_version} {args.optimization} {args.gp}"
            )
            print(f"  size=0x{size:X} words={size // WORD_SIZE} output={args.output}")
            if args.keep_intermediates:
                print(f"  intermediates={workspace}")
            return 0
        finally:
            if not args.keep_intermediates:
                shutil.rmtree(workspace, ignore_errors=True)
    except RetailError as exc:
        print(f"build_candidate: ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
