# Plan 4 — wrap the port, then scale matching

Plans 1–3 are complete (retail registration through PAC extraction). This plan
answers Checkpoint P and Checkpoint A in one stroke: the port stops at an asset
viewer until decompiled game code exists to host, and decompression stays
unexplored until a chunk type is shown to need it. Effort then moves to
matching, which is the long pole.

```
[W1] viewer takes any TMD ──→ [W2] find TMDs in chunks ──→ [W3] status docs
                                                                  │
[D1] regenerate disassembly ──→ [D2] batch harness ──→ [D3] sweep ──→ [D4] one substantive hand match
```

## Phase W — port wrap-up (bounded)

### W1. The viewer renders any extracted TMD
`render_tmd` grows `--model PATH`, keeping the pinned model as the default so
ctest is unchanged. Rotation continues across frames so a viewer can see all
sides.
*Acceptance:* ctest `render_tmd` still passes; a second extracted TMD renders
with `--model` and `--screenshot`.
*Verify:* ctest, plus one manual screenshot of a different model.

### W2. Locate TMDs inside PAC chunks
`tools/find_tmd.py` scans an extracted chunk for candidate TMD headers and
keeps only those `tmd.py` parses cleanly to the end. This links A2 to P2: from
archive to screen through tools alone.
*Acceptance:* unit-tested on synthetic chunks; finds the P2 model in member 37
chunk 0 at `0x8800`; refuses false positives.
*Verify:* `python3 tools/find_tmd.py extracted/pac/sc01/0037_000.bin`.

### W3. Status docs
`docs/PC-PORT.md` gains a status section: what runs, what does not, and that
Windows is unverified here because no MinGW toolchain is installed. Checkpoint
P is recorded as decided.
*Acceptance:* a reader can run every target from the docs alone.

### ✅ Checkpoint W — port paused as a viewer; move to decomp

## Phase D — matching at scale

### D1. Regenerate the disassembly
`asm/` is untracked and was found empty. Regenerate from
`config/splat.template.yaml` against the pinned executable and record the
exact command in `docs/MATCHING.md` so this never costs a session again.
*Acceptance:* every function in `provenance/matches.json` re-verifies through
the oracle against the regenerated tree.

### D2. Batch harness that cannot destroy work
`tools/batch_match.py`: for each function, m2c → build → oracle in a scratch
directory. It **refuses** to write a path that already exists under `src/`,
promotes only exact matches, and appends to `matches.json`. The overwrite
incident in `docs/MATCHING.md` is the test case.
*Acceptance:* unit tests for refuse-to-overwrite, promote-on-match, and
discard-on-mismatch; no child without `stdin=DEVNULL` and a timeout.

### D3. Sweep the main executable
Run D2 over every function splat emits. Commit the matches with the
trivial/substantive split from `progress.py`.
*Acceptance:* `progress.py` reports more substantive matches than 3; every
new entry re-verifies.

### D4. One substantive hand match on the boot path
Pick the first non-trivial function on the entry chain (`main` or the overlay
loader) that the batch failed on. Decompile by hand, iterate against the
oracle, commit the match with notes on what m2c got wrong.
*Acceptance:* oracle exit 0; `docs/MATCHING.md` records the idioms learned.

### ✅ Checkpoint D — report the match rate; decide whether to keep sweeping or target the boot path

## Conventions
- RED before GREEN; one commit per task; stage only that task's files.
- Every child process: `stdin=DEVNULL`, timeout.
- Addresses and formats come from bytes, never from notes.
- Retail-derived data (asm, extracted, models, chunks) stays untracked.
- A build is not a match. Only the oracle says match.
