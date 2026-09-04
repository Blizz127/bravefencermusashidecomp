# Todo (third plan)

Detail, acceptance criteria and verification are in [plan.md](plan.md).
Check an item off only once the full suite and `./tools/run_tests.sh` pass and
the task is committed.

## Phase P — Render a real model

- [x] **P2a** `tools/tmd.py` — TMD parser, pure and unit-tested (14 tests)
  - [x] offsets resolve relative to `base + 12`, the object table start
  - [x] refusals: wrong `id`, object table past EOF, primitive walk not ending
        exactly at `vert_top`, non-polygon mode, vertex block not ending at
        `normal_top`, out-of-range indices, and the two payload variants it
        does not read (textured, and `flag & 0x04` per-vertex colour)
  - [x] parses `SC01.CD` `0xA97000` into 18 vertices, 16 normals, 18
        primitives — 2 gouraud triangles, 16 gouraud quads; bounds
        x[-5,5] y[-10,0] z[-5,5]
- [x] **P2b** `tools/extract_tmd.py` — extracts the model to a standalone file
      (736 bytes, sha256 `5f1ad117…`), output untracked, 8 tests
  - [x] length measured by walking the model, since a TMD carries no total size
  - [x] refuses a non-TMD offset, a truncated model, an offset past the archive,
        and overwriting an existing output
- [x] **P2c** Renders the model: `RotTransPers` per vertex, `POLY_G3`/`POLY_G4`
      via `addPrim`, `DrawOTag`; verified headless as ctest `render_tmd`
  - [x] inside sampled rgb5 (29,24,18) against the model's authored (30,24,19);
        corner still the clear colour — proves it drew, not just exited
  - [x] skips (not fails) when the untracked model is absent or `xvfb-run` is
        missing; `--screenshot` works; `render_quad` and all matches still pass
  - [x] **`USE_PGXP` stays off**, as planned
  - [x] fixed the 64-bit width hazard a third time: `RotTransPers` takes `int*`,
        not `long*`
  - [x] pixel judge rewritten as a per-channel tolerance — the dominant-channel
        heuristic rejected the model's beige as wrong

- [ ] **⏸ Checkpoint P**

## Phase A — Assets (carried forward from the second plan, unchanged)

- [x] **A1** PAC layout walked: `SC01.CD` is itself a `.CD` archive of 86
      members, 78 of them PAC containers holding 199 chunks. 100.0000% of the
      PAC region covered, zero gaps, zero overlaps. Recorded in
      `docs/ASSETS.md`
  - [x] D1's key was half right: the `u32` at `+12` is a **length**, not a
        pointer. The two coincide for 56 of 198 chunks, which is why the
        pointer reading survived casual checking
  - [x] the framing was the real error — a flat scan finds all 199 headers but
        no walk closes until the archive is read as nested
- [x] **A2** `tools/extract_pac.py`, fail-closed, 16 unit tests, output
      untracked; extracts all 199 chunks with per-chunk SHA-256

- [ ] **⏸ Checkpoint A** — decide on LZSS if type-4 chunks require it

## Standing constraints

- [ ] RED before GREEN; one commit per task; stage only that task's files
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] formats and addresses observed from bytes, never taken from notes —
      three notes have now been wrong (PAC layout, an overlay base, TMD offsets)
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification; a clean
      exit is not a rendered frame
