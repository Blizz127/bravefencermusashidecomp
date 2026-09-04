# Plan (third)

Supersedes the second plan. Its hygiene and decomp tasks (H0–H1, D1–D4) and P1
are complete. **A1 and A2 are now complete as well**; every task in this
plan is done.

## Context

Twenty commits in. The compiler is resolved (GCC 2.7.2 / PSY-Q 4.0 / ASPSX
2.56), 25 functions match byte-exactly, member 0012 of `MAIN.CD` is split with
2431 functions labelled, and the PC port renders a quad through the Psy-Q layer
verified headlessly in CI.

P2 renders a real model from the disc, walking a TMD onto `libgpu` primitives
rather than adopting the GPL-3.0 `libgs`.

### The TMD format is already solved

Planning derived and verified it, so P2 does not have to. **Offsets in the
object table are relative to `base + 12`** — the start of the object table
itself, not the file base and not the end of the header. That interpretation
was found by noticing that a naive walk overshot `vert_top` by exactly 12 bytes
on *two* independent models of very different sizes, which is systematic rather
than noise.

Four checks pass on both `0xA97000` (18 primitives) and `0x685800` (92):

- `prim_top` lands exactly at the end of the object table;
- walking `n_primitive` packets, each `4 + ilen*4` bytes, ends exactly at
  `vert_top`;
- the vertex block is `n_vert` eight-byte vectors ending exactly at
  `normal_top`;
- every packet's mode byte is a polygon.

### The target model needs no textures

`SC01.CD` at `0xA97000`: one object, 18 vertices, 16 normals, 18 primitives.
Its mode bytes are **only** `0x30` (gouraud triangle, ×2) and `0x38` (gouraud
quad, ×16). Nothing textured, nothing semi-transparent.

So P2 needs `POLY_G3` and `POLY_G4` and no TIM loading at all. The other model
at `0x685800` carries four textured quads (`0x3C`) and is deliberately *not*
the target, keeping textures out of this slice.

### One decision this forces

`USE_PGXP` is currently off, because with it on `VERTTYPE` is a 16-bit half
float in C++ and a `short` in C, so coordinates written from C are read as
float16 denormals. P1 records that it stays off "until the port has real GTE
transforms". P2 introduces exactly those.

**It stays off.** Turning it on requires every `VERTTYPE` write in decomp C to
go through PsyCross's `_HF()` macro, which is invasive and buys nothing until
sub-pixel precision matters. P2 records the constraint rather than paying for
it now.

## Dependency graph

```
[P2a] TMD parser (pure, tested) ──┐
                                  ├──→ [P2c] render the model, verified headless
[P2b] extract + pin the model ────┘

[A1] PAC format reverse-engineered ──→ [A2] PAC parser
```

P2a and P2b are independent of each other. Phase A is independent of all of P2
and unblocked; D1 already found its likely key, that the `u32` at `+12` of a
PAC header points at the next chunk.

---

## Phase P — Render a real model

### P2a. TMD parser

`tools/tmd.py`, pure and unit-tested against synthetic fixtures. Parse the
header, the object table, and the primitive packets using the verified
`base + 12` offset rule.

Fail closed in the style of `extract_cd.py`. A misparsed model does not error,
it produces plausible garbage geometry.

*Acceptance:*
- refuses a wrong `id`, an object table running past end of file, a primitive
  walk that does not end exactly at `vert_top`, a non-polygon mode byte, and a
  vertex block that does not end at `normal_top`;
- parses the real model at `0xA97000` into 18 vertices, 16 normals and 18
  primitives classified as 2 gouraud triangles and 16 gouraud quads;
- reports vertex indices and per-vertex colours per primitive.

*Verify:* `python3 -m pytest tests/test_tmd.py -q`, then run it against the
real model and check the counts above.

### P2b. Extract and pin the model

The renderer must not read `SC01.CD` directly; retail data is addressed by hash
everywhere else in this project and models should be no different. Add a mode
to extract a TMD by offset into an ignored directory, recording size and
SHA-256, exactly as `extract_cd.py` does for archive members.

*Acceptance:* the model at `0xA97000` extracts to a standalone file with its
digest recorded; the output is untracked; extracting a range that is not a TMD
is refused.

*Verify:* the tool's own output, plus `git status` staying clean.

### P2c. Render the model, verified headless

Extend the port with a TMD walker over `libgpu`: `InitGeom`, `SetGeomOffset`,
`SetGeomScreen`, a rotation and translation via `SetRotMatrix`/`SetTransMatrix`,
`RotTransPers` per vertex, then `POLY_G3`/`POLY_G4` emitted with `addPrim` into
the ordering table and drawn with `DrawOTag`.

Reuse what P1 established: the ordering table is `OT_TAG[]`, `ClearOTagR` chains
backwards so the head is `ot[n-1]`, and verification reads framebuffer 0 with
`glReadPixels` before `PsyX_EndScene`.

Verification asserts the model is actually on screen, not merely that the
program exited: a sample inside the projected model differs from the clear
colour, and a corner sample still holds the clear colour. Judging stays in
`tools/vram_pixel.py` so it remains unit-tested.

*Acceptance:* a new ctest target passes headless under `xvfb-run`, skipping
loudly where no virtual display exists; `--screenshot` produces a viewable
frame; the existing `render_quad` test and all decomp matches still pass.

*Verify:* `./tools/run_tests.sh`, then
`xvfb-run -a ctest --test-dir build -R render_tmd`.

### ✅ Checkpoint P — a real asset renders; decide how much further the port goes

---

## Phase A — Assets (carried forward unchanged)

### ✅ A1. Reverse-engineer the PAC chunk format

The researched layout does not match the bytes: neither candidate length field
walks from one chunk to the next across `SC01.CD`'s 199 chunks. Establish the
real layout by walking the archive and finding the field that advances with no
gaps and no overlaps.

D1 supplies the likely key. In `MAIN.CD` member 0012 the `u32` at `+12` of the
first PAC header holds `0x27800`, which is exactly where the second header
sits.

*Acceptance:* a documented layout under which a walk covers 100% of the
archive's PAC region with zero gaps or overlaps, and the observed type-byte set
recorded in `docs/ASSETS.md`.
*Verify:* the walk script's coverage report.
*Result:* met. 199 chunks, 17,707,008 of 17,707,008 bytes, all 78 PAC members
closing on their exact declared end. `+12` is a length, not a pointer, and
`SC01.CD` is a nested `.CD` archive — see docs/ASSETS.md.

### ✅ A2. PAC parser

`tools/extract_pac.py`, fail-closed like `extract_cd.py`: refuse a truncated
header, a chunk past end of file, and a walk that does not reach the archive
end.

*Acceptance:* unit-tested with synthetic fixtures; extracts every chunk from
`SC01.CD` with per-chunk size and SHA-256; output untracked.
*Verify:* `python3 tools/extract_pac.py extracted/disc/files/SC01.CD --output …`.
*Result:* met. 16 unit tests; the real run reports 199 chunks at 100.0000%
coverage and skips the eight `.sqv` members by magic rather than forcing them.

### ✅ Checkpoint A — assets reachable; decide on LZSS if type-4 chunks need it

---

## Conventions

- RED before GREEN on every task; one commit per task; stage only that task's
  files.
- Pure logic gets unit tests; subprocess and GL glue stays thin; every child
  process gets `stdin=DEVNULL` and a timeout.
- Formats and addresses are **observed from bytes**, never taken from external
  notes. Three notes have now been wrong: the PAC layout, an overlay load
  address, and the TMD offset base.
- Retail-derived data — disassembly, extracted members, models, chunks — stays
  untracked.
- A build is not a match; a match is not a compiler identification; a program
  that exits cleanly has not necessarily drawn anything.
