# Todo — plan 4

## Phase W — port wrap-up
- [x] **W1** viewer fits any TMD from its vertex bounds; `--frames N` spins it; ctest unchanged
- [x] **W2** `tools/find_tmd.py`: 8 tests; finds 4 models in member 37 chunk 0, the P2 one at payload offset 0x87F0
- [x] **W3** `docs/PC-PORT.md` status rewritten: what runs, what does not, Windows unverified (no MinGW)
- [x] **⏸ Checkpoint W** — port paused as a viewer on 2026-09-03; effort moves to matching

## Phase D — matching at scale
- [x] **D1** `asm/` regenerated for main and both overlays; commands in MATCHING.md; `tools/verify_registry.py` re-verifies 25/25
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
