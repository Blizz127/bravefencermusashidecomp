# Plan

## Context

Eleven commits in. Provenance is pinned, the disc extracts faithfully, splat
covers 99.50% of `SLUS_007.26`, and a verified build-and-compare loop exists.
`docs/ROADMAP.md` is the spec; there is no `SPEC.md`.

What actually blocks progress is narrower than it looks:

- **Only relocation-free leaf functions can be matched at all.** Anything with
  a `jal` or a `%hi`/`%lo` global reference compiles to bytes containing
  unresolved relocations, which cannot be compared with linked retail bytes.
  That is the large majority of the 1334 static functions. 1 is matched.
- **Most of the game is not in those 1334 functions.** Gameplay logic streams
  from disc overlays loaded past `0x80074800`. The `.CD` archive format is
  documented and verified — `LIST.CD` parses to 49 entries — but nothing reads
  it yet.
- **The compiler is narrowed to three, unreplicated.** PSY-Q 3.5 / 4.0 / 4.1
  survive; 4.3 / 4.4 / 4.5 are eliminated on one function. A replication
  attempt was inconclusive.
- **The PC port is 55 lines of plumbing** with no Psy-Q shims, so nothing can
  render.

The ordering below is deliberate: the link step is placed ahead of finishing
compiler identification, because it unlocks ~1300 more matchable functions and
every additional match is free compiler evidence. Grinding on the compiler
first optimises the wrong constraint.

## Dependency graph

```
[0] roadmap contradiction fix ── independent, trivial

[1] link/relocation step ──┬─→ [2] compiler resolution (more evidence available)
                           └─→ [4] overlay function matching

[3] .CD archive reader ────────→ [4] overlay split + match

[5] PsyCross shim layer ───────→ [6] first rendered artifact
     (independent of 1-4; needs no decomp progress)
```

Phases 1–2 and phase 3 are independent tracks. Phase 3 can proceed in parallel
or be deferred entirely.

---

## Phase A — Unlock matching at scale

### A0. Fix the roadmap contradiction

`docs/ROADMAP.md` line 49 states no function has been matched; line 57 states
one has. Leftover from incremental edits.

*Acceptance:* the file states the matched count once, consistently.
*Verify:* read the file; `grep -c "first match"`.

### A1. Link step so relocated functions can be matched

Today `build_candidate.py` extracts a symbol's bytes straight from the `.o`,
so any `jal` or `%hi`/`%lo` reference is an unresolved relocation and the
comparison is meaningless. Add a link stage that resolves those against known
addresses and emits final, comparable bytes.

Splat already emits exactly the needed inputs in linker-assignment syntax:
`config/undefined_syms.auto.txt` and `config/undefined_funcs.auto.txt` contain
`name = 0xADDR;` lines. Feed them to `mips-linux-gnu-ld` with the section
placed at the function's vram, then `objcopy -O binary`.

Reuse: `build_candidate._run`/`_capture` (already carry the `stdin=DEVNULL`
and timeout guards that `maspsx` requires), `parse_nm_symbols`, `slice_symbol`,
`default_toolchain_root`, `default_maspsx_path`.

*Acceptance:*
- Pure, unit-tested generation of the linker script / `--defsym` set from the
  auto symbol files, including a malformed-line case.
- One function containing a `jal` matches byte-exactly end to end.
- Existing relocation-free matches are unaffected.

*Verify:*
```sh
python3 -m pytest tests/ -q && ./tools/run_tests.sh
python3 tools/build_candidate.py src/main/80012ab0.c --symbol func_80012AB0 --output /tmp/a.bin
python3 tools/match_function.py --vram 0x80012AB0 --size 0xC --candidate /tmp/a.bin   # still MATCH
```

### A2. Resolve the compiler with the enlarged candidate pool

With relocated functions matchable, pick two or three genuinely complex,
structurally *independent* functions and run `tools/discriminate.py` on each.
Independence matters: the previous replication attempt initially reached for
`func_80013028`, which shares a signature and logic with the first target and
would have confirmed itself.

The sharpest known signal is return-delay-slot filling after `jr $ra` —
2.8.1 fills it, 2.7.2 does not — and retail leaves it unfilled in
`func_80012E6C` while gcc-2.7.2 filled it. Worth a dedicated look.

*Acceptance:* either the surviving set narrows below three with agreement
across at least two independent functions, or the ambiguity is recorded with
the reason it cannot be resolved by this method. A null result is a valid
outcome and must not be dressed up as identification — `docs/COMPILER-ID.md`
governs.

*Verify:* `tools/discriminate.py` output recorded in `docs/MATCHING.md` for
each function; elimination sets agree.

### ✅ Checkpoint A

Relocated functions are matchable and the compiler question is either resolved
or explicitly parked with evidence. **Stop and review before Phase B** — if the
compiler narrows to one, matching flags are settled and later work is cheaper;
if not, decide whether to proceed on the three-candidate set.

---

## Phase B — Reach the overlays

### B1. `.CD` archive reader

Format (documented, and `LIST.CD` verified to parse): `0x800` header holding
`u32 file_count`, `u32 pad`, then 8 bytes per entry — `u32 start_sector`
(× `0x800`) and `u32 size`. Sub-files are padded to `0x800`. `LIST.CD` holds
the headers of the other `.CD` files and is loaded at boot.

*Acceptance:*
- Pure, unit-tested header parsing with synthetic fixtures, including refusal
  on a truncated header, an entry running past end-of-file, and a count that
  disagrees with the data present.
- Extracts `MAIN.CD` into an ignored directory and reports each member's size
  and SHA-256.
- Extracted output stays untracked, consistent with the retail-data policy in
  `LICENSE-NOTES.md`.

*Verify:*
```sh
python3 tools/extract_cd.py extracted/disc/files/MAIN.CD --output extracted/overlays/main
python3 -m pytest tests/ -q
```

### B2. Split and match one overlay function

Add a splat config for one extracted overlay at its load address, produce a
disassembly, and match one function inside it through the existing oracle.
This is the vertical proof that the overlay path works end to end — not just
that files can be unpacked.

Load addresses are a genuine unknown. They must be **observed**, not assumed:
derive them from the loader code in the static executable, or from the overlay
header if one exists. Do not copy addresses from third-party notes without
verifying them against the bytes.

*Acceptance:* one overlay function matches byte-exactly, with its load address
justified by evidence recorded alongside the config.

*Verify:* `tools/match_function.py` reports MATCH for that function.

### ✅ Checkpoint B

The majority of the game's code is reachable and provably matchable. **Stop and
review** — this is the point to decide how much matching to pursue before
shifting effort toward the port.

---

## Phase C — First runnable output (independent track)

Deliberately scoped to *prove the shim path*, not to port the game. This can
run in parallel with A and B, or be skipped.

### C1. Vendor PsyCross and link decomp C against it

PsyCross (MIT) reimplements libgpu, libgte, libspu, libcd, libetc, libapi and
libpad for PC and is used by REDRIVER2 and CTR Native. Vendor it at a pinned
commit via `tools/fetch_toolchains.sh`, following the existing `fetch_pinned`
pattern, and gitignore the checkout.

**Licensing constraints established by research and recorded here so they are
not rediscovered the hard way:** libValkyrie has no LICENSE file — do not
vendor. psyz is split-licensed and its `include/` and `src/psyq` are
unlicensed Sony-derived headers. PSXRecomp and MusashiRecomp are PolyForm
Noncommercial, so no code may be taken from them.

*Acceptance:* the existing CMake target builds and links against PsyCross on
Linux with the smoke binary still passing.

*Verify:* `./tools/run_tests.sh`.

### C2. One visible artifact

Render a single primitive or decode one asset through the shim layer — enough
to prove the path from decomp-owned C to pixels. Not a game loop.

**Known gap, unavoidable:** no permissively-licensed `libgs` exists. BFM is 3D
and will need TMD rendering eventually. The only working PC `libgs` is in the
Silent Hill decomp and is GPL-3.0. Options are to design around it at the
libgpu/ordering-table level, treat that implementation as a specification to
study rather than copy, or accept GPL-3.0. **This is a licensing decision for
the user, not a technical one — surface it before writing TMD code.**

*Acceptance:* a window renders one primitive, driven by decomp-owned C.
*Verify:* run it and capture a screenshot.

### ✅ Checkpoint C

The port path is proven viable, or its blocking constraint (libgs licensing) is
surfaced for a decision.

---

## Conventions that apply to every task

- RED before GREEN: a failing test first, minimum code to pass, then the full
  suite and `./tools/run_tests.sh`.
- One commit per task so any point is a clean rollback; stage only that task's
  files, never `git add -A`.
- Pure logic gets unit tests; subprocess glue stays thin. Every child process
  gets explicit `stdin=DEVNULL` and a timeout — `maspsx` reads stdin when it is
  not a tty and otherwise hangs forever.
- Retail-derived data — disassembly, extracted files, overlays, fetched
  toolchains — stays untracked.
- Claims are bounded by evidence. A build that succeeds is not a match, a match
  is not a compiler identification, and a null result gets recorded as one.
