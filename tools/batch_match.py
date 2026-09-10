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
import progress
from retail_common import RetailError, load_json, write_json_atomic

CHILD_TIMEOUT_SECONDS = 120
OPTIMIZATION_CANDIDATES = ("-O2", "-O0")
GLABEL_RE = re.compile(r"^\s*glabel\s+(\S+)\s*$")
# /* fileofs vram bytes */  mnemonic ...
INSTRUCTION_RE = re.compile(
    r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s+(\w+)(.*)$"
)
GTE_OPCODES = frozenset({
    "ctc2", "cfc2", "mtc2", "mfc2", "lwc2", "swc2", "cop2",
    "sdc2", "ldc2",
    "rtps", "rtpt", "nclip", "avsz3", "avsz4", "mvmva",
    "ncds", "ncdt", "nccs", "ncct", "ncs", "nct", "cc", "cdp",
    "dpcs", "dpcl", "dpct", "intpl", "sqr0", "sqr12", "sqr", "op",
    "gpf", "gpl",
})


@dataclass(frozen=True)
class FunctionRange:
    name: str
    vram: int
    size: int
    is_direct_jump_thunk: bool = False


@dataclass(frozen=True)
class Outcome:
    name: str
    status: str  # match | mismatch | build-failed | m2c-failed | skipped-existing
    optimization: str | None = None

    @property
    def promoted(self) -> bool:
        return self.status == "match"


def enumerate_functions(text: str) -> list[FunctionRange]:
    """Every `glabel` in a splat disassembly, sized by its instruction words.

    Size comes from counting the instruction comments rather than subtracting
    the next label's address, so trailing padding between functions is not
    silently folded into the one before it.  Some splat labels occur in the
    middle of a fall-through function; those are folded into the preceding
    entry until a terminating jump closes the range.
    """

    found: list[FunctionRange] = []
    name: str | None = None
    vram: int | None = None
    words = 0
    terminal_transfer = False
    transfer_pending = False
    jr_ra_pending = False
    forward_target = 0
    last_address = 0
    opcodes: list[str] = []

    def flush() -> None:
        nonlocal name, vram, words, terminal_transfer, opcodes
        nonlocal transfer_pending, jr_ra_pending, forward_target, last_address
        if (name is not None and vram is not None and words > 0
                and terminal_transfer and last_address >= forward_target):
            found.append(
                FunctionRange(
                    name=name,
                    vram=vram,
                    size=words * 4,
                    is_direct_jump_thunk=opcodes == ["j", "nop"],
                )
            )
        name, vram, words, terminal_transfer, opcodes = None, None, 0, False, []
        transfer_pending, jr_ra_pending, forward_target, last_address = False, False, 0, 0

    for line in text.splitlines():
        # Splat emits alignment nops outside endlabel. Honor this boundary
        # only after all known forward paths and the transfer delay slot;
        # an endlabel at a misidentified interior split is not authority.
        if re.match(r"^\s*endlabel\s+\S+\s*$", line):
            if terminal_transfer and last_address >= forward_target:
                flush()
            continue
        label = GLABEL_RE.match(line)
        if label:
            if name is None:
                name = label.group(1)
            elif terminal_transfer and last_address >= forward_target:
                flush()
                name = label.group(1)
            continue
        instruction = INSTRUCTION_RE.match(line)
        if instruction:
            address = int(instruction.group(1), 16)
            opcode = instruction.group(3)
            if name is None:
                # Alignment nops between jr $ra tails are not their own function.
                if opcode == "nop":
                    continue
                name = f"func_{address:08X}"
            if vram is None:
                vram = address
            # A transfer is not complete until its contiguous delay slot.
            completed_jr_ra = (
                transfer_pending
                and jr_ra_pending
                and address == last_address + 4
            )
            terminal_transfer = transfer_pending and address == last_address + 4
            transfer_pending = opcode in {"j", "jr"}
            jr_ra_pending = opcode == "jr" and bool(re.search(r"\$ra\b", line))
            if transfer_pending:
                terminal_transfer = False
            # Decode the signed PC-relative displacement from the instruction
            # bytes, not potentially misidentified function/local label names.
            if opcode in {"b", "beq", "bne", "beqz", "bnez", "bgez",
                          "bgtz", "blez", "bltz", "bc0f", "bc0t", "bc2f", "bc2t"}:
                word = int.from_bytes(bytes.fromhex(instruction.group(2)), "little")
                displacement = word & 0xFFFF
                if displacement & 0x8000:
                    displacement -= 0x10000
                forward_target = max(forward_target, address + 4 + displacement * 4)
            last_address = address
            opcodes.append(opcode)
            words += 1
            # A jr $ra that no earlier path jumps past ends this callable even
            # when splat did not emit a following glabel.
            if completed_jr_ra and last_address >= forward_target:
                terminal_transfer = True
                flush()
    flush()
    return found


def instruction_words(text: str, function: FunctionRange) -> list[tuple[int, int, str]]:
    """Retail instruction words inside ``function``, from splat comments."""

    return [(addr, word, opcode) for addr, word, opcode, _text in instruction_lines(text, function)]


def instruction_lines(text: str, function: FunctionRange) -> list[tuple[int, int, str, str]]:
    """Retail instructions inside ``function``: address, word, opcode, splat text."""

    end = function.vram + function.size
    found: list[tuple[int, int, str, str]] = []
    for line in text.splitlines():
        instruction = INSTRUCTION_RE.match(line)
        if instruction is None:
            continue
        address = int(instruction.group(1), 16)
        if address < function.vram or address >= end:
            continue
        word = int.from_bytes(bytes.fromhex(instruction.group(2)), "little")
        opcode = instruction.group(3)
        rest = instruction.group(4) or ""
        stmt = (opcode + rest).split("/*", 1)[0].strip()
        found.append((address, word, opcode, stmt))
    return found


def function_contains_gte(text: str, function: FunctionRange) -> bool:
    """True when ordinary C cannot emit the cop2/GTE ops in this range."""

    return any(opcode in GTE_OPCODES for _addr, _word, opcode in instruction_words(text, function))


# GNU as knows these cop2 encodings; DMPSX fake ops (mvmva, rtps, ...) need
# `.word` of the retail encoding because gas has no such mnemonics.
GAS_KNOWN_GTE = frozenset({
    "ctc2", "cfc2", "mtc2", "mfc2", "lwc2", "swc2", "cop2", "sdc2", "ldc2",
})
# maspsx inserts delay nops for these even under `.set noreorder`, which
# shifts later labels. Keep the retail encoding instead.
MASPSX_EXPANDS = frozenset({
    "b", "beq", "bne", "beqz", "bnez", "bgez", "bgtz", "blez", "bltz",
    "bc0f", "bc0t", "bc2f", "bc2t",
    "jal", "jalr", "j",
    # splat `break 7` is PSY-Q code 7<<10; maspsx rewrites it as GNU
    # `break 0x0,0x7` (code 7) and the word no longer matches retail.
    "break",
})
_SPLAT_LABEL_RE = re.compile(r"^\s*(\.L[0-9A-Fa-f]+)\s*:")
_PAREN_IMM_RE = re.compile(
    r"\((0x[0-9A-Fa-f]+)\s*(>>|<<|&|\|)\s*(0x[0-9A-Fa-f]+|\d+)\)"
)


def _escape_asm(stmt: str) -> str:
    return stmt.replace("\\", "\\\\").replace('"', '\\"')


def _eval_paren_immediate(match: re.Match[str]) -> str:
    """Splat writes `lui $at, (0x80000000 >> 16)`; maspsx cannot parse that."""

    left = int(match.group(1), 16)
    operator = match.group(2)
    right = int(match.group(3), 0)
    if operator == ">>":
        value = left >> right
    elif operator == "<<":
        value = left << right
    elif operator == "&":
        value = left & right
    else:
        value = left | right
    return f"0x{value & 0xFFFFFFFF:X}"


def compact_overlay_stmt(stmt: str) -> str:
    """Make splat mnemonics maspsx-parseable.

    maspsx splits `sltu $v0, $v0, $v1` on whitespace, so the first operand
    token is `$v0,` and a later 3-tuple unpack crashes. cc1 emits
    `sltu $v0,$v0,$v1`. Parenthesized splat immediates are evaluated here
    because maspsx is not an expression parser.
    """

    stmt = _PAREN_IMM_RE.sub(_eval_paren_immediate, stmt)
    return re.sub(r"\s*,\s*", ",", stmt)


def assembly_overlay_source(
    function: FunctionRange,
    words: list[tuple[int, int, str]] | list[tuple[int, int, str, str]],
    listing: str | None = None,
) -> str:
    """Mnemonic GTE/cop2 overlay. Ordinary C cannot emit cop2.

    Regular MIPS and gas-known cop2 use splat mnemonics. DMPSX fake ops
    (`mvmva`, `rtps`, ...) become a single `.word` of the retail encoding.
    A whole-function `.word` dump is refused.
    """

    has_gte = False
    word_ops = 0
    mnemonic_ops = 0
    body_lines: list[str] = []
    pending_labels: list[str] = []
    emitted_addrs: set[int] = set()

    def emit_labels() -> None:
        for label in pending_labels:
            body_lines.append(f'    "{_escape_asm(label)}:\\n"')
        pending_labels.clear()

    def emit_op(opcode: str, word: int, stmt: str) -> None:
        nonlocal has_gte, word_ops, mnemonic_ops
        if opcode in GTE_OPCODES:
            has_gte = True
        if (opcode in GTE_OPCODES and opcode not in GAS_KNOWN_GTE) or opcode in MASPSX_EXPANDS:
            body_lines.append(f'    ".word 0x{word:08X}\\n"')
            word_ops += 1
        else:
            compact = compact_overlay_stmt(" ".join(stmt.split()))
            body_lines.append(f'    "{_escape_asm(compact)}\\n"')
            mnemonic_ops += 1

    if listing is not None:
        end = function.vram + function.size
        for line in listing.splitlines():
            label = _SPLAT_LABEL_RE.match(line)
            instruction = INSTRUCTION_RE.match(line)
            if instruction:
                address = int(instruction.group(1), 16)
                if address < function.vram or address >= end:
                    pending_labels.clear()
                    continue
                emit_labels()
                opcode = instruction.group(3)
                rest = instruction.group(4) or ""
                stmt = (opcode + rest).split("/*", 1)[0].strip()
                word = int.from_bytes(bytes.fromhex(instruction.group(2)), "little")
                emit_op(opcode, word, stmt)
                emitted_addrs.add(address)
            elif label and not instruction:
                pending_labels.append(label.group(1))
    else:
        for item in words:
            if len(item) == 4:
                _addr, word, opcode, stmt = item
            else:
                _addr, word, opcode = item
                stmt = opcode
            emit_op(opcode, word, stmt)

    if not has_gte:
        raise RetailError(
            f"{function.name}: refusing a non-GTE assembly overlay; "
            "ordinary-C-emittable ranges must be recovered as C"
        )
    if word_ops and word_ops >= mnemonic_ops:
        raise RetailError(
            f"{function.name}: refusing a .word dump overlay; "
            "GTE ranges must keep MIPS mnemonics"
        )
    body = "\n".join(body_lines)
    return (
        '#include "psx_types.h"\n\n'
        "/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.\n"
        " * Verified by tools/match_function.py. */\n"
        "__asm__(\n"
        '    ".set noreorder\\n"\n'
        f'    ".globl {function.name}\\n"\n'
        f'    ".type {function.name}, @function\\n"\n'
        f'    "{function.name}:\\n"\n'
        f"{body}\n"
        f'    ".size {function.name}, .-{function.name}\\n"\n'
        '    ".set reorder\\n"\n'
        ");\n"
    )


def m2c_assembly_text(text: str, function: FunctionRange) -> str:
    """Make m2c see labels inside a coalesced range as internal labels.

    Splat may start a new ``glabel`` after a fall-through instruction even
    though the CPU has not returned.  m2c treats that marker as a hard
    function boundary.  Rewriting only labels strictly inside this bounded
    function to ``alabel`` preserves all instructions and branch targets while
    allowing the decompiler to reconstruct the full control-flow graph.
    """

    lines = text.splitlines(keepends=True)
    labels: list[tuple[int, int]] = []
    for index, line in enumerate(lines):
        if not GLABEL_RE.match(line):
            continue
        for candidate in lines[index + 1 :]:
            if GLABEL_RE.match(candidate):
                break
            instruction = INSTRUCTION_RE.match(candidate)
            if instruction:
                labels.append((index, int(instruction.group(1), 16)))
                break

    end = function.vram + function.size
    for index, vram in labels:
        if function.vram < vram < end:
            # Replace only the directive: GLABEL_RE also consumes the line
            # ending, which must remain separate from the next instruction.
            lines[index] = lines[index].replace("glabel", "alabel", 1)
    return "".join(lines)


def source_path(repo: Path, region: str, vram: int) -> Path:
    """Where a matched source for this function would live."""

    stem = f"{vram & 0xFFFFFFFF:08x}".lstrip("0") or "0"
    if region == "main":
        return repo / "src" / "main" / f"{stem}.c"
    return repo / "src" / "overlays" / region / f"{stem}.c"


def banked_candidate_path(candidate_dir: Path | None, function: FunctionRange) -> Path | None:
    """Return an existing banked draft for ``function``, if one was requested."""

    if candidate_dir is None:
        return None
    candidate = candidate_dir / f"{function.name}.c"
    return candidate if candidate.is_file() else None


def should_attempt(target: Path, function: FunctionRange | None = None) -> bool:
    """False for existing source or a direct-jump thunk m2c cannot express."""

    return not target.exists() and not (function and function.is_direct_jump_thunk)


def promoted_entry(
    function: FunctionRange,
    region: str,
    source: str,
    source_text: str,
    optimization: str | None,
) -> dict[str, Any]:
    """Registry row for a freshly promoted complete function.

    Recovery is classified from the source that produced the bytes, not from
    the filename. Batch enumeration only yields complete functions.
    """

    entry: dict[str, Any] = {
        "name": function.name,
        "vram": function.vram,
        "size": function.size,
        "region": region,
        "source": source,
        "recovery": progress.classify_recovery(source_text),
        "extent": "function",
    }
    if optimization is not None:
        entry["optimization"] = optimization
    return entry


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
FUNCPTR_RE = re.compile(r"\?\s*\(\*\s*(\w*)\s*\)\s*\([^;()]*\)")
FUNCPTR_DEF_RE = re.compile(r"^(\s*)\?\s*\(\*(\w+)\(([^;()]*)\)\)\(\)\s*\{", re.MULTILINE)
FUNCPTR_PROTO_RE = re.compile(r"\?(\s*\(\*\w+\([^;()]*\)\)\([^;()]*\)\s*;)")
NAMED_PARAM_RE = re.compile(r"([(,]\s*)\?(\s+\w+)")
NULL_MACRO_RE = re.compile(r"\bNULL\b")
EXTERN_S32_RE = re.compile(r"^(\s*)extern s32 (\w+);", re.MULTILINE)
EXTERN_UNKNOWN_RE = re.compile(r"^(\s*extern\s+)\?\s+(\w+\s*;)", re.MULTILINE)
BARE_PARAM_RE = re.compile(r"([(,]\s*)\?(?=\s*[,)])")
CALL_RE = re.compile(r"\b(\w+)\(")


def _sanitize(source: str) -> str:
    """Replace m2c's `?` placeholders with something the compiler accepts.

    m2c cannot see a symbol defined outside the functions it was asked to
    decompile, so it marks its type `?`, which is not valid C. `?` shows up in
    several shapes here, and they need different fixes. A final rule maps
    the NULL macro to 0 (-nostdinc provides no definition):

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
    * A named `? arg` parameter becomes `s32 arg`. A ternary cannot match:
      the `?` must directly follow `(` or `,` and be followed by a name.
    * A definition `? (*name(args))() {` becomes `s32 name(args) {`. m2c
      spells a function it believes returns a function pointer this way;
      the observed bodies return a register value, which s32 carries.
    * A prototype `? (*name(args))(retargs);` becomes
      `s32 (*name(args))(retargs);`. Only the `?` changes, so a call
      through the returned pointer is undisturbed.
    * An m2c `Warning: ...` diagnostic line is dropped. It is emitted on
      stdout, so the harness captures it as part of the candidate body,
      and it is never valid C.
    """

    # m2c diagnostics ride along on captured stdout; they are never C.
    source = "\n".join(
        line for line in source.splitlines() if not line.startswith("Warning:")
    )
    if source:
        source += "\n"

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

    source = FUNCPTR_DEF_RE.sub(r"\1s32 \2(\3) {", source)
    source = FUNCPTR_RE.sub(r"s32 (*\1)()", source)
    source = FUNCPTR_PROTO_RE.sub(r"s32\1", source)
    source = PROTO_RE.sub(proto, source)
    source = LOCAL_VAR_RE.sub(lambda m: f"{m.group(1)}s32 {m.group(2)};", source)
    source = UNKNOWN_ARGS_RE.sub("()", source)
    source = UNKNOWN_POINTER_RE.sub("void *", source)
    source = EXTERN_UNKNOWN_RE.sub(r"\1s32 \2", source)
    source = NAMED_PARAM_RE.sub(r"\1s32\2", source)
    source = BARE_PARAM_RE.sub(r"\1s32", source)
    # m2c spells the zero address NULL, but -nostdinc leaves it undefined.
    # A plain 0 generates identical code wherever a null pointer fits.
    source = NULL_MACRO_RE.sub("0", source)
    return _declare_missing_symbols(_refine_extern_pointers(source))


def _declare_missing_symbols(source: str) -> str:
    """Declare referenced-but-undeclared D_/func_ symbols.

    m2c occasionally uses a symbol it never declares. A bare use that is
    called (`NAME(`) gets the unchecked `void NAME();` prototype; any
    other bare use gets `extern s32 NAME;`. Anything already declared —
    plain declarations, `extern`, and `(*NAME)` callback forms — is
    evidence the symbol is known and is left alone, so this pass can
    neither duplicate nor contradict an existing declaration.
    """

    declared = set()
    for pattern in (
        # Context may declare globals with typedef or tagged-struct types.
        # Their explicit extern declarations take precedence over guessing.
        r"^([ \t]*)extern[ \t]+[^;{}()\n]*?\b((?:D_|func_)\w+)\b",
        r"^(\s*)(?:extern\s+)?(?:s32|void|u32|u16|u8|s16|s8|char|int|short|long|unsigned)\b[^(;{}]*\b((?:D_|func_)\w+)\b",
        r"\(\*\s*((?:D_|func_)\w+)\b",
    ):
        declared.update(
            match.group(2 if pattern.startswith("^") else 1)
            for match in re.finditer(pattern, source, re.M)
        )
    missing = []
    for match in re.finditer(r"\b((?:D_|func_)\w+)\b", source):
        name = match.group(1)
        if name in declared or name in missing:
            continue
        missing.append(name)
    if not missing:
        return source
    body = re.sub(r"/\*.*?\*/", "", source, flags=re.S)
    decls = []
    for name in missing:
        # Skip names whose only sites vanished with the comments.
        if re.search(r"\b" + name + r"\b", body) is None:
            continue
        if re.search(r"\b" + name + r"\s*\(", body) is not None:
            decls.append(f"void {name}();")
        else:
            decls.append(f"extern s32 {name};")
    if not decls:
        return source
    anchor = re.search(r"^#include.*$", source, re.M)
    if anchor is None:
        return "\n".join(decls) + "\n" + source
    at = anchor.end()
    return source[:at] + "\n" + "\n".join(decls) + source[at:]


def _refine_extern_pointers(source: str) -> str:
    """Narrow `extern s32` to a pointer when every use demands it.

    A symbol m2c only ever dereferences (`*D = v`) holds an address, so
    `extern s32` cannot compile and `extern s32 *D` is forced. One called
    through (`(*D)(x)`) is a callback and needs `extern s32 (*D)()`.
    A symbol with any plain value-use (`D = v`, `f(D)`) keeps s32: mixed
    uses are contradictory without layout knowledge and stay loud for
    hand work. Comments are ignored so `/* static */` cannot vote.
    """

    found = EXTERN_S32_RE.findall(source)
    if not found:
        return source
    scrubbed = re.sub(r"/\*.*?\*/", "", source, flags=re.S)
    nodecl = EXTERN_S32_RE.sub("", scrubbed)
    for _indent, name in found:
        called_through = (
            re.search(r"\(\*\s*" + name + r"\s*\)\s*\(", nodecl) is not None
        )
        stripped = re.sub(r"\*\s*" + name + r"\b", "", nodecl)
        stripped = re.sub(r"\b" + name + r"\s*\[", "", stripped)
        stripped = re.sub(r"&\s*" + name + r"\b", "", stripped)
        value_use = re.search(r"\b" + name + r"\b", stripped) is not None
        if called_through:
            replacement = f"extern s32 (*{name})();"
        elif stripped != nodecl and not value_use:
            replacement = f"extern s32 *{name};"
        else:
            continue
        source = re.sub(
            r"^(\s*)extern s32 " + name + r";",
            lambda match: match.group(1) + replacement,
            source,
            flags=re.M,
        )
    return source


DRAFT_HEADER_TEMPLATE = (
    "/* m2c draft from {asm}: NOT verified against retail. C89-gated only;\n"
    " * promotion requires an oracle MATCH (tools/match_function.py). Types\n"
    " * and signatures are whatever the decompiler guessed; they are not\n"
    " * evidence of the original declaration. */\n"
)

VERIFIED_HEADER_TEMPLATE = (
    "/* Decompiled by m2c from {asm}, then verified byte-exact\n"
    " * against retail by tools/match_function.py. Types and signatures are\n"
    " * whatever reproduces the bytes; they are not evidence of the\n"
    " * original declaration. */\n"
)


def run_m2c(
    m2c: Path, asm: Path, function: str, output: Path, *, display_asm_name: str | None = None
) -> bool:
    """Decompile one function. Every child gets a closed stdin and a timeout.

    The candidate is stamped as an unverified draft: the verified claim
    is only ever added by stamp_verified, after the oracle MATCH.
    """

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
        + DRAFT_HEADER_TEMPLATE.format(asm=display_asm_name or asm.name)
        + "\n"
        + _sanitize(result.stdout)
    )
    return True


def stamp_verified(produced: Path, asm_name: str) -> None:
    """Replace the draft header with the verified claim, in place.

    Called only after the oracle MATCH for this exact file. A file
    without the draft block (e.g. hand-provided) gets the verified
    header prepended instead of a second copy.
    """

    draft = DRAFT_HEADER_TEMPLATE.format(asm=asm_name)
    verified = VERIFIED_HEADER_TEMPLATE.format(asm=asm_name)
    text = produced.read_text()
    if draft in text:
        produced.write_text(text.replace(draft, verified, 1))
    else:
        produced.write_text(verified + "\n" + text)


def _quiet(fn, argv: list[str]) -> int:
    sink = io.StringIO()
    with contextlib.redirect_stdout(sink), contextlib.redirect_stderr(sink):
        return fn(argv)


def verify_existing(
    function: FunctionRange,
    region: str,
    target_spec: dict[str, Any],
    source: Path,
    scratch: Path,
) -> Outcome:
    """Compile an on-disk source without modifying it.

    Used to register sources that already exist under src/ but have no
    registry row. The file is copied into scratch so stamping cannot
    touch the original. MATCH here is not a promotion.
    """

    if not source.is_file():
        return Outcome(function.name, "skipped-missing")

    produced = scratch / f"{function.name}.c"
    shutil.copyfile(source, produced)
    original = source.read_bytes()
    candidate = scratch / "candidate.bin"
    candidate.unlink(missing_ok=True)

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

    built = False
    for optimization in OPTIMIZATION_CANDIDATES:
        candidate.unlink(missing_ok=True)
        code = _quiet(
            build_candidate.main,
            [
                str(produced),
                "--symbol", function.name,
                "--link-base", f"0x{function.vram:X}",
                f"--optimization={optimization}",
                "--output", str(candidate),
            ],
        )
        if code != 0 or not candidate.is_file():
            continue
        built = True
        if _quiet(match_function.main, match_argv) != 0:
            continue
        if source.read_bytes() != original:
            raise RetailError(
                f"refusing to continue: existing source changed during verify: {source}"
            )
        return Outcome(function.name, "match", optimization)

    if source.read_bytes() != original:
        raise RetailError(
            f"refusing to continue: existing source changed during verify: {source}"
        )
    return Outcome(function.name, "mismatch" if built else "build-failed")


def attempt(
    function: FunctionRange,
    region: str,
    target_spec: dict[str, Any],
    repo: Path,
    asm: Path,
    m2c: Path,
    scratch: Path,
    candidate_dir: Path | None = None,
) -> Outcome:
    """Build and compare one function. Promote only on MATCH.

    When supplied, ``candidate_dir`` is an opt-in cache of previously
    C89-gated m2c drafts.  It saves a fresh m2c invocation but is never
    trusted: each draft still compiles through the retail toolchain and must
    pass the same byte-for-byte comparison before it can leave scratch.
    """

    target = source_path(repo, region, function.vram)
    if not should_attempt(target, function):
        return Outcome(function.name, "skipped-existing")

    produced = scratch / f"{function.name}.c"
    candidate = scratch / "candidate.bin"
    candidate.unlink(missing_ok=True)

    asm_text = asm.read_text()
    gte_overlay = function_contains_gte(asm_text, function)
    if gte_overlay:
        # cop2/GTE cannot be emitted from ordinary C; overlay the retail
        # words and still require an oracle MATCH before promotion.
        produced.write_text(
            assembly_overlay_source(
                function, instruction_lines(asm_text, function), listing=asm_text
            )
        )
    else:
        banked = banked_candidate_path(candidate_dir, function)
        if banked is not None:
            # Copy into scratch so stamping/promoting never mutates the candidate
            # bank.  The bank is a convenience cache, not an authority.
            shutil.copyfile(banked, produced)
        else:
            # The source disassembly remains untouched.  m2c receives a private
            # copy whose labels have the correct boundary for this one coalesced
            # range.
            m2c_asm = scratch / f"{function.name}.s"
            m2c_asm.write_text(m2c_assembly_text(asm_text, function), encoding="utf-8")

            if not run_m2c(m2c, m2c_asm, function.name, produced, display_asm_name=asm.name):
                return Outcome(function.name, "m2c-failed")

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

    built = False
    optimizations = ("-O2",) if gte_overlay else OPTIMIZATION_CANDIDATES
    for optimization in optimizations:
        code = _quiet(
            build_candidate.main,
            [
                str(produced),
                "--symbol", function.name,
                "--link-base", f"0x{function.vram:X}",
                f"--optimization={optimization}",
                "--output", str(candidate),
            ],
        )
        if code != 0 or not candidate.is_file():
            continue
        built = True
        if _quiet(match_function.main, match_argv) != 0:
            continue

        if not gte_overlay:
            stamp_verified(produced, asm.name)
        promote(produced, target)
        return Outcome(function.name, "match", None if gte_overlay else optimization)

    return Outcome(function.name, "mismatch" if built else "build-failed")


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asm", type=Path, required=True, help="splat disassembly, e.g. asm/main.s")
    parser.add_argument("--region", default="main", help="registry region name for these functions")
    parser.add_argument("--registry", type=Path, help="default: provenance/matches.json")
    parser.add_argument("--m2c", type=Path, help="default: tools/m2c/m2c.py")
    parser.add_argument(
        "--candidate-dir",
        type=Path,
        help=("optional directory of C89-gated m2c drafts; each is still compiled and "
              "byte-compared before promotion"),
    )
    parser.add_argument(
        "--banked-only",
        action="store_true",
        help="with --candidate-dir, skip entries that have no banked draft instead of rerunning m2c",
    )
    parser.add_argument("--limit", type=int, help="try at most this many functions")
    parser.add_argument("--min-vram", type=lambda value: int(value, 0), default=0,
                        help="skip functions below this runtime address")
    parser.add_argument("--min-size", type=int, default=0, help="skip functions smaller than this many bytes")
    parser.add_argument("--max-size", type=int, default=256, help="skip functions larger than this many bytes")
    parser.add_argument("--dry-run", action="store_true", help="list what would be attempted and stop")
    parser.add_argument(
        "--register-existing",
        action="store_true",
        help=("verify sources already under src/ that have no registry row; "
              "register on MATCH without copying or deleting anything"),
    )
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
        if args.candidate_dir is not None and not args.candidate_dir.is_dir():
            raise RetailError(f"candidate directory not found: {args.candidate_dir}")
        if args.banked_only and args.candidate_dir is None:
            raise RetailError("--banked-only requires --candidate-dir")
        registry = load_json(registry_path)
        targets = registry.get("targets", {})
        if args.region not in targets:
            raise RetailError(f"region {args.region!r} is not a registered target in {registry_path}")
        target_spec = targets[args.region]

        functions = enumerate_functions(args.asm.read_text())
        registered_vrams = {m["vram"] for m in registry.get("matches", []) if m.get("region") == args.region}
        if args.register_existing:
            pending = [
                f for f in functions
                if f.vram >= args.min_vram and args.min_size <= f.size <= args.max_size
                and f.vram not in registered_vrams
                and source_path(repo, args.region, f.vram).is_file()
            ]
        else:
            pending = [
                f for f in functions
                if f.vram >= args.min_vram and args.min_size <= f.size <= args.max_size
                and should_attempt(source_path(repo, args.region, f.vram), f)
            ]
        if args.banked_only:
            pending = [f for f in pending if banked_candidate_path(args.candidate_dir, f) is not None]
        if args.limit is not None:
            pending = pending[: args.limit]

        if args.register_existing:
            print(f"{len(functions)} functions in {args.asm}; {len(pending)} existing sources to verify "
                  f"(<= {args.max_size} bytes, not yet registered)")
        else:
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
                target = source_path(repo, args.region, function.vram)
                if args.register_existing:
                    outcome = verify_existing(
                        function, args.region, target_spec, target, scratch
                    )
                else:
                    outcome = attempt(
                        function,
                        args.region,
                        target_spec,
                        repo,
                        args.asm,
                        m2c,
                        scratch,
                        args.candidate_dir,
                    )
                outcomes.append(outcome)
                if outcome.promoted:
                    entry = promoted_entry(
                        function,
                        args.region,
                        str(target.relative_to(repo)),
                        target.read_text(),
                        outcome.optimization,
                    )
                    if entry["recovery"] not in {"c", "assembly"}:
                        # Byte-identical .word dumps compile, but they are not
                        # decompilation. classify_recovery already excludes
                        # them from unique coverage; do not register them.
                        outcomes[-1] = Outcome(function.name, "unclassified-dump")
                        if index % 25 == 0:
                            print(f"  [{index}/{len(pending)}] ...")
                        continue
                    promoted.append(function)
                    register(
                        registry,
                        registry_path,
                        entry,
                    )
                    print(f"  [{index}/{len(pending)}] MATCH {function.name} "
                          f"({function.size} bytes) -> {target}")
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
