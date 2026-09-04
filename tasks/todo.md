# Todo — plan 4

## Phase W — port wrap-up
- [ ] **W1** `render_tmd --model PATH`, continuous rotation, pinned default unchanged
- [ ] **W2** `tools/find_tmd.py` finds parseable TMDs inside a PAC chunk; unit-tested
- [ ] **W3** `docs/PC-PORT.md` status section; Windows recorded as unverified (no MinGW)
- [ ] **⏸ Checkpoint W**

## Phase D — matching at scale
- [ ] **D1** regenerate `asm/` from the splat template; command recorded; registry re-verifies
- [ ] **D2** `tools/batch_match.py` — scratch-dir only, refuses existing `src/` paths, promotes exact matches
- [ ] **D3** sweep the main executable; commit matches; substantive count > 3
- [ ] **D4** one hand match on the boot path
- [ ] **⏸ Checkpoint D**

## Standing constraints
- [ ] RED before GREEN; one commit per task; stage only that task's files
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] formats and addresses observed from bytes, never taken from notes
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification
