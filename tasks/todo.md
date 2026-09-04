# Todo (second plan)

Detail, acceptance criteria and verification are in [plan.md](plan.md).
Check an item off only once the full suite and `./tools/run_tests.sh` pass and
the task is committed.

## Hygiene

- [x] **H0** Deleted the stray `pc_port/psycross.cmake` (confirmed by the user);
      nothing referenced it and the build is unaffected
- [x] **H1** Build-time guard against `ResetCallback`/`VSyncCallback` references
      from decomp code (64-bit pointer truncation in `LIBETC.C`); proven to fire
      by introducing a reference, then restored

## Phase D — Decomp depth

- [ ] **D1** Symbol discovery for `MAIN.CD` member 0012
  - [ ] generator from prologues **and** in-span `jal` targets (frameless
        leaves have no prologue), unit-tested
  - [ ] `config/overlay_main_0012.yaml` at base `0x80100158`, evidence recorded
  - [ ] splat splits 100% and labels ≥ 2,000 functions
- [ ] **D2** First byte-exact match inside member 0012 (proves the path)
- [ ] **D3** Scale matching to ≥ 25 functions; `tools/progress.py` counts
      functions in real C, never match percentage
- [ ] **D4** *(optional)* separate PSY-Q 3.5 / 4.0 / 4.1 — only if a verified
      match happens to disagree; do not hunt

- [ ] **⏸ Checkpoint D**

## Phase P — Port rendering

- [ ] **P1** One `POLY_F4` quad, verified headless via `GR_ReadVRAM` under
      `xvfb-run` + llvmpipe; separate `ctest` target, smoke test stays
      display-free
- [ ] **P2** TMD walker on `libgpu` primitives (`RotTransPers` + `addPrim`),
      unit-tested parser, renders the 18-primitive model at `SC01.CD`
      `0xA97000` headlessly — does **not** wait on PAC work

- [ ] **⏸ Checkpoint P**

## Phase A — Assets

- [ ] **A1** Reverse-engineer the PAC chunk layout from `SC01.CD` — research
      claim is wrong; acceptance is a gap-free, overlap-free walk of all 199
      chunks, recorded in `docs/ASSETS.md`
- [ ] **A2** `tools/extract_pac.py`, fail-closed, unit-tested, output untracked

- [ ] **⏸ Checkpoint A** — decide on LZSS if type-4 chunks require it

## Standing constraints

- [ ] RED before GREEN; one commit per task; stage only that task's files
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] addresses and formats observed from bytes, never copied from notes
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification
