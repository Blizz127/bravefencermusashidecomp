# Plan (second)

Supersedes the first plan, whose implementation tasks (A0–C1) are all done.

## Context

Sixteen commits in. Three functions match byte-exactly, one of them inside an
overlay. The compiler is narrowed to three candidates (PSY-Q 3.5 / 4.0 / 4.1)
on replicated evidence. The PC port links against PsyCross and reaches a real
Psy-Q layer, proven headlessly.

Two decisions, made by the user, shape this plan:

- **Both tracks proceed in parallel.** Decomp depth and port rendering are
  independent, and each has unblocked work.
- **TMD rendering is built on `libgpu` primitives.** No permissively licensed
  `libgs` exists; rather than adopt the GPL-3.0 one, the port walks TMDs
  itself using `RotTransPers` and `addPrim`. More work; no license constraint.

Facts established during planning that change what to build — several of
them *correct* earlier assumptions:

- **Member 0012 of `MAIN.CD` is the real code payload.** Of 49 members only
  two are code. Member 0007 is 9.6 KB; member 0012 is **548 KB with ~1,865
  stack-frame prologues**, more functions than the entire static executable.
  The static `SLUS_007.26` split is the minority of the game.
- **Its load address is `0x80100158`, and it is one segment.** The
  call-target-to-prologue method used for member 0007 gives a clear winner
  (102 sampled hits against 12 for the runner-up) but only 72% full
  verification. That gap is explained, not ignored: the missed targets begin
  with `lui`/`load`/`alu` — real first instructions of **frameless leaf
  functions**, which produce no prologue. Prologue count is a floor. The 60
  out-of-span targets cluster at `0x800C…`/`0x800D…`, exactly where member 0007
  lives, so they are calls to the other overlay, not a second segment.
- **The researched PAC chunk layout is wrong for this disc.** Neither
  candidate length field walks from one chunk to the next. A PAC parser must
  begin by reverse-engineering the format against the bytes, not by
  implementing the research claim.
- **Real TMD models exist at raw offsets in `SC01.CD`** — one with 92
  primitives, one with 18. This decouples "render a model" from the PAC work
  entirely.
- **Headless rendering is proven, not assumed.** `xvfb-run` plus Mesa
  llvmpipe yields a GL 4.6 core context on this machine, and PsyCross
  publicly exports `GR_ReadVRAM`/`GR_SaveVRAM`. Rendering tasks can assert on
  pixels in CI.
- **The `libgs` gap is empirical.** The built archive exports zero `Gs*`
  symbols against 399 Psy-Q functions.

## Dependency graph

```
[H0] stray psycross.cmake ── user confirms delete ── independent
[H1] 64-bit callback hazard guard ───────────────── independent

Decomp track
[D1] 0012 symbol discovery ──→ [D2] 0012 split + first match ──→ [D3] scale matching
                                                                └─→ [D4] compiler separation (optional)

Port track                                  Asset track
[P1] first quad, headless-verified          [A1] PAC format reverse-engineered
        │                                          │
        └──→ [P2] TMD walker on libgpu      [A2] PAC parser ──→ (feeds P3 later)
              (uses raw SC01.CD TMD;
               does NOT depend on A1/A2)
```

D, P and A are independent of one another. P2 deliberately sources its model
from a raw `SC01.CD` offset so the port is not blocked behind PAC work.

---

## Hygiene

### H0. Resolve the stray `pc_port/psycross.cmake`

A second PsyCross integration appeared mid-session, authored by something
other than this work. It is wired into nothing and carries the case-sensitive
glob bug that silently drops the whole Psy-Q layer. It should be deleted, but
it is not ours to delete unasked.

*Acceptance:* file removed **after explicit confirmation**, and
`git status` clean.
*Verify:* `test ! -e pc_port/psycross.cmake && ./tools/run_tests.sh`.

### H1. Guard the 64-bit callback truncation

`LIBETC.C` returns a callback pointer as an `int`; on x86-64 that truncates.
The build downgrades the error, but any decomp code that stores and re-installs
the value from `ResetCallback`/`VSyncCallback` would silently corrupt a
pointer. Without patching the vendored tree, add a compile-time or link-time
guard that fails if those two symbols are referenced from decomp-owned C.

*Acceptance:* referencing either from `src/` or `pc_port/` fails the build
with a message naming the hazard; the smoke target is unaffected.
*Verify:* a temporary reference fails; removing it restores green.

---

## Phase D — Decomp depth

### D1. Symbol discovery for member 0012

splat labels only what it can infer without symbols; on member 0007 that was
2 of 19 functions. Generate `config/symbol_addrs.main_0012.txt` from two
sources, in splat's `name = 0xADDR; // type:func` syntax:

1. every stack-frame prologue offset;
2. every in-span `jal` target — this is what catches frameless leaf
   functions, which have no prologue and are otherwise invisible.

Reuse `identify_compiler.parse_disassembly` and the `jal`-decoding logic
already used in planning. Pure generation logic gets unit tests with a
synthetic member; the real run is verification.

*Acceptance:*
- unit-tested generator, including refusal on an entry outside the member;
- a `splat` config `config/overlay_main_0012.yaml` at base `0x80100158`
  (evidence recorded in the file as for member 0007) splits **100%** of the
  member and labels **≥ 2,000** functions.
*Verify:* `python3 -m splat split config/overlay_main_0012.yaml` reports 100%;
`grep -c ^glabel asm/overlays/main_0012/main_0012.s`.

### D2. First byte-exact match inside member 0012

Pick a small, relocation-light function, decompile with m2c, match through the
oracle in blob mode against the hash-pinned member. This proves the 0012 path
end to end; the load address is confirmed by a function matching at all.

*Acceptance:* one function in 0012 reports `MATCH`, with `--link-base` set to
the function's address.
*Verify:* the `build_candidate`/`match_function` pair as in `docs/OVERLAYS.md`.

### D3. Scale matching

With ~2,000 functions labelled, match in volume. Track progress honestly per
the rr-decomp lesson recorded in `docs/MATCHING.md`: count **functions in real
C**, never `objdiff` percentage or `__asm__` transcription. Add a
`tools/progress.py` that reports matched-function count and bytes, with tests.

*Acceptance:* ≥ 25 functions matched across the executable and both overlays;
`progress.py` output recorded in `docs/MATCHING.md`.
*Verify:* `python3 tools/progress.py`; every listed function re-verifies
through the oracle.

### D4. Separate the last three compiler candidates (optional)

Only if D3 surfaces a verified match on which the three survivors *disagree*
— `discriminate.py` will show it. Do not go hunting; the answer arrives free
as matching proceeds. If it never does, record that PSY-Q 3.5/4.0/4.1 are
indistinguishable on this codebase and move on.

### ✅ Checkpoint D — review before scaling further

---

## Phase P — Port rendering

### P1. One flat-shaded quad, verified headless

Decomp-owned C initialises PsyCross, submits a `POLY_F4` via `setPolyF4`,
`setRGB0`, `setXY4`, `addPrim` into an ordering table, draws with `DrawOTag`
and syncs. Verification reads the framebuffer back with `GR_ReadVRAM` and
asserts the quad's colour at a covered pixel and the clear colour outside it.

Runs under `xvfb-run` with `LIBGL_ALWAYS_SOFTWARE=1`, so it is a real CI test,
not a screenshot someone has to look at. Add it as a `ctest` target separate
from the smoke test; the smoke test must stay display-free.

*Acceptance:* new `ctest` target passes headless; `run_tests.sh` runs it when
`xvfb-run` is present and skips loudly when not.
*Verify:* `xvfb-run -a ctest --test-dir build -R render_quad`.

### P2. Render one TMD model through `libgpu` primitives

The `libgs`-free path chosen by the user. Write a TMD walker that reads the
header (`FIXP` flag, object table), transforms vertices with `SetRotMatrix`,
`SetTransMatrix`, `RotTransPers`, and emits `POLY_F3`/`POLY_F4` primitives via
`addPrim`. Source the model from the **18-primitive TMD at `SC01.CD` offset
`0xA97000`** — a raw, verified header — so this does not wait on PAC work.

The TMD parser is pure and unit-tested against a synthetic TMD (header,
object table, one flat triangle). Rendering is verified headless as in P1 by
asserting that the model's covered pixels differ from the clear colour.

*Acceptance:* unit-tested parser refuses a bad `id`, an object table past EOF,
and a primitive count that disagrees with the data; the 18-primitive model
renders headlessly with ≥ 1 non-clear pixel in the expected region.
*Verify:* `xvfb-run -a ctest --test-dir build -R render_tmd`.

### ✅ Checkpoint P — the port path is proven; decide how far to take it

---

## Phase A — Assets

### A1. Reverse-engineer the PAC chunk format

The research claim does not match the bytes. Establish the real layout by
walking `SC01.CD`: for each `PAC\0` header, find the field that advances to
the next header with no gaps and no overlaps across all 199 chunks. Record the
type byte values observed and what each seems to contain.

*Acceptance:* a documented layout under which a walk covers **100%** of the
archive's PAC region with zero gaps or overlaps; the observed type set
recorded in `docs/ASSETS.md`.
*Verify:* the walk script's coverage report.

### A2. PAC parser

Implement the layout from A1 as `tools/extract_pac.py`, fail-closed in the
style of `extract_cd.py`: refuse a truncated header, a chunk past EOF, and a
walk that does not reach the archive end.

*Acceptance:* unit-tested with synthetic fixtures; extracts every chunk from
`SC01.CD` with per-chunk size and SHA-256; output untracked.
*Verify:* `python3 tools/extract_pac.py extracted/disc/files/SC01.CD --output …`.

### ✅ Checkpoint A — assets reachable; decide on LZSS if type-4 chunks need it

---

## Conventions

- RED before GREEN on every task; one commit per task; stage only that task's
  files.
- Pure logic gets unit tests; subprocess glue stays thin; every child process
  gets `stdin=DEVNULL` and a timeout.
- Load addresses and formats are **observed from bytes**, never copied from
  external notes — two of those notes were wrong during this planning pass.
- Retail-derived data — disassembly, extracted members, chunks, models — stays
  untracked.
- A build is not a match; a match is not a compiler identification; matched
  progress is counted in functions of real C.
