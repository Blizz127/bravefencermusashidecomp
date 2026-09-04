# Todo

Task detail, acceptance criteria and verification steps are in
[plan.md](plan.md). Check items off only once the full suite and
`./tools/run_tests.sh` pass and the task is committed.

## Phase A — Unlock matching at scale

- [x] **A0** Fix the `docs/ROADMAP.md` contradiction (line 49 says no function
      matched, line 57 says one is)
- [x] **A1** Link step: resolve relocations from splat's `*.auto.txt` so
      functions with `jal` / `%hi` / `%lo` become comparable
  - [x] unit-tested generation of linker symbol definitions, incl. malformed input
  - [x] one function containing a `jal` matches byte-exactly
        (`func_80014128`, 8/8 words)
  - [x] existing relocation-free matches unaffected
  - [x] addresses also derived from splat symbol names, for callees inside the
        split that the auto files do not list
  - [x] stale output cleared before building, after a failed build left bytes
        that `match_function` reported a false MATCH on
- [x] **A2** Resolve the compiler using the enlarged pool of matchable functions
  - [x] pick structurally *independent* functions
  - [x] run `tools/discriminate.py` on each; elimination sets agree
        (`func_80012E6C` and `func_80014128` both eliminate 4.3 / 4.4 / 4.5)
  - [x] examine return-delay-slot filling after `jr $ra` — this is the concrete
        difference: retail restores `$sp` before `jr $ra` and leaves the slot
        empty; the 2.8.x line fills it with the restore
  - [x] record the outcome in `docs/MATCHING.md`
  - [x] eliminate on failure to reproduce a *verified* source, not only on
        instruction count — a 100% match proves the C, making failure decisive
  - [ ] **outcome: narrowed to three, not one.** PSY-Q 3.5 / 4.0 / 4.1 all
        reproduce both verified functions exactly. Separating them needs a
        verified match on a high-register-pressure function
        (`func_800346D0`, `func_800435CC`), which requires type modelling.

- [ ] **⏸ Checkpoint A** — review before starting Phase B

## Phase B — Reach the overlays

- [x] **B1** `.CD` archive reader
  - [x] unit-tested header parsing (truncated header, entry past EOF, bad count,
        zero count, entry starting inside the header)
  - [x] extracts `MAIN.CD` — 49 members, 5,985,664 bytes — reporting per-member
        size and SHA-256, with an optional JSON manifest
  - [x] output untracked; refuses to overwrite an existing directory
- [x] **B2** Split and match one overlay function
  - [x] load address **observed** — `0x800CEDF8` for `MAIN.CD` member 0007,
        derived from two independent lines of evidence, not from an external
        memory map (see `docs/OVERLAYS.md`)
  - [x] splat config for one overlay (`config/overlay_main_0007.yaml`),
        splitting 100% of the member
  - [x] one overlay function matches byte-exactly (`func_800CF3B0`, 22/22)
  - [x] oracle extended to compare against a hash-pinned blob, since overlay
        addresses fall outside the executable's text range

- [ ] **⏸ Checkpoint B** — decide how much matching to pursue before porting

## Phase C — First runnable output (independent track)

- [x] **C1** Vendor PsyCross (MIT) at a pinned commit; link the CMake target
      against it
  - [x] vendored at `e56e4cde`, fetched by `tools/fetch_toolchains.sh`
  - [x] decomp-owned C calls into the Psy-Q layer and gets verified results
        (`rcos(0)=4096`, `rsin(1024)=4096`); headless, so CI needs no GPU
  - [x] `-DMUSASHI_WITH_PSYCROSS=OFF` path verified, so the decomp tooling still
        builds on a machine with no graphics stack
  - [x] four upstream defects worked around; see `docs/PC-PORT.md`
  - [x] did **not** vendor libValkyrie (no LICENSE), psyz `include/` or
        `src/psyq` (unlicensed Sony-derived), or anything from PSXRecomp /
        MusashiRecomp (PolyForm Noncommercial)
- [ ] **C2** Render one primitive from decomp-owned C
  - [x] `libgs` gap now confirmed empirically, not just from research: the built
        archive exports **zero** `Gs*` symbols against 399 Psy-Q functions
  - [ ] **decision needed from the user before any TMD code is written** —
        build on `libgpu`/ordering-table primitives, study the GPL-3.0 Silent
        Hill implementation as a spec without copying, or accept GPL-3.0

- [ ] **⏸ Checkpoint C** — port path proven, or its blocker surfaced

## Standing constraints

- [ ] RED before GREEN on every task; one commit per task
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification
