# Todo

Task detail, acceptance criteria and verification steps are in
[plan.md](plan.md). Check items off only once the full suite and
`./tools/run_tests.sh` pass and the task is committed.

## Phase A — Unlock matching at scale

- [ ] **A0** Fix the `docs/ROADMAP.md` contradiction (line 49 says no function
      matched, line 57 says one is)
- [ ] **A1** Link step: resolve relocations from splat's `*.auto.txt` so
      functions with `jal` / `%hi` / `%lo` become comparable
  - [ ] unit-tested generation of linker symbol definitions, incl. malformed input
  - [ ] one function containing a `jal` matches byte-exactly
  - [ ] existing relocation-free matches unaffected
- [ ] **A2** Resolve the compiler using the enlarged pool of matchable functions
  - [ ] pick 2–3 structurally *independent* complex functions
  - [ ] run `tools/discriminate.py` on each; elimination sets must agree
  - [ ] examine return-delay-slot filling after `jr $ra` as the sharpest signal
  - [ ] record the outcome in `docs/MATCHING.md`, including a null result

- [ ] **⏸ Checkpoint A** — review before starting Phase B

## Phase B — Reach the overlays

- [ ] **B1** `.CD` archive reader
  - [ ] unit-tested header parsing (truncated header, entry past EOF, bad count)
  - [ ] extracts `MAIN.CD`, reporting per-member size and SHA-256
  - [ ] output untracked
- [ ] **B2** Split and match one overlay function
  - [ ] load address **observed** from loader code or overlay header, not assumed
  - [ ] splat config for one overlay
  - [ ] one overlay function matches byte-exactly

- [ ] **⏸ Checkpoint B** — decide how much matching to pursue before porting

## Phase C — First runnable output (independent track)

- [ ] **C1** Vendor PsyCross (MIT) at a pinned commit; link the CMake target
      against it
  - [ ] do **not** vendor libValkyrie (no LICENSE), psyz `include/` or
        `src/psyq` (unlicensed Sony-derived), or anything from PSXRecomp /
        MusashiRecomp (PolyForm Noncommercial)
- [ ] **C2** Render one primitive from decomp-owned C
  - [ ] surface the `libgs` licensing decision **before** writing TMD code —
        no permissive implementation exists

- [ ] **⏸ Checkpoint C** — port path proven, or its blocker surfaced

## Standing constraints

- [ ] RED before GREEN on every task; one commit per task
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification
