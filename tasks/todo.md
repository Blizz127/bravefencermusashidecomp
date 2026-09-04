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

- [x] **D1** Symbol discovery for `MAIN.CD` member 0012
  - [x] generator from prologues **and** in-span `jal` targets, unit-tested
        (17 tests); 2215 starts found, 350 of them frameless leaves invisible
        to prologue scanning
  - [x] **correction: the member is a PAC container, not raw.** splat
        disassembling it as data exposed it. Data chunk at `0x0`, code chunk at
        `0x28000` loading at `0x80128158`; discovery is region-restricted
  - [x] `config/overlay_main_0012.yaml` with the container structure recorded
  - [x] whole member accounted for (`unknown: 0 B`; the 70.15% figure is the
        code chunk's share, not a gap) and **2431 functions labelled**
- [x] **D2** First byte-exact match inside member 0012 (`func_8012BF4C`, 2/2)
  - [x] fixed a silent-wrong-bytes bug it exposed: the linked image starts at
        `.text`'s real address, not the requested base, since `ld` rounds up to
        the section alignment
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
