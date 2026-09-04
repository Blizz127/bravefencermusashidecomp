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
- [ ] **P2b** Extract and pin the model to a standalone file, size + SHA-256
      recorded, output untracked; a range that is not a TMD is refused
- [ ] **P2c** Render it: `RotTransPers` per vertex, `POLY_G3`/`POLY_G4` via
      `addPrim`, `DrawOTag`; verified headless
  - [ ] a sample inside the projected model differs from the clear colour, and
        a corner still holds the clear colour — proves it drew, not just exited
  - [ ] new ctest target; skips loudly without `xvfb-run`; `--screenshot` works
  - [ ] `render_quad` and all decomp matches still pass
  - [ ] **`USE_PGXP` stays off** — turning it on needs `_HF()` on every
        `VERTTYPE` write in C, and buys nothing until sub-pixel precision does

- [ ] **⏸ Checkpoint P**

## Phase A — Assets (carried forward from the second plan, unchanged)

- [ ] **A1** Reverse-engineer the PAC chunk layout from `SC01.CD` — the
      researched claim is wrong; acceptance is a gap-free, overlap-free walk of
      all 199 chunks, recorded in `docs/ASSETS.md`
  - [ ] likely key from D1: the `u32` at `+12` of a PAC header points at the
        next chunk
- [ ] **A2** `tools/extract_pac.py`, fail-closed, unit-tested, output untracked

- [ ] **⏸ Checkpoint A** — decide on LZSS if type-4 chunks require it

## Standing constraints

- [ ] RED before GREEN; one commit per task; stage only that task's files
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] formats and addresses observed from bytes, never taken from notes —
      three notes have now been wrong (PAC layout, an overlay base, TMD offsets)
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification; a clean
      exit is not a rendered frame
