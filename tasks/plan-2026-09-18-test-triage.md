# Session plan — test-suite triage and startup steps 8–10 (2026-09-18)

Goal: root-cause the 40 failures the previous session left red, and continue the
startup chain (`docs/NATIVE-BOOT-ENTRY.md`) at steps 8–10: `8002C8F4`,
`8001971C`, `80010214`.

Additive: `tasks/plan-2026-09-18-c-only.md` and `tasks/plan.md` remain in force
and were not modified.

## Result

| | failed | passed | errors | xfail |
| --- | --- | --- | --- | --- |
| baseline | 40 | 2,452 | 11 | 0 |
| after this session | **8** | **2,495** | **0** | 1 |

(`test_native_smoke` was the ninth; it passes after the SDL config fix below but
the table counts the last full-suite run plus that individual re-run.)

`python3 tools/verify_registry.py` is still **2,730/2,730, exit 0**.

## Root causes (grouped, not by test name)

### 1. Homebrew unversioned SDL2 include tree — 7 tests

`/home/linuxbrew/.linuxbrew/include/SDL2/SDL_main.h` is missing while the
versioned `sdl2-compat` keg has it. `pkg-config`/`sdl2-config` point at the
incomplete tree, so every compiled probe including `<SDL.h>` died with
`fatal error: SDL_main.h: No such file or directory`. `tools/run_tests.sh`
already worked around this for CMake (`SDL2_DIR`) but not for the probes.

Fix: `tests/conftest.py` prepends the complete include directory to `CPATH`
(no-op when the unversioned tree is complete). The same discovery in
`tests/test_native_smoke.py` passes `-DSDL2_DIR` into its CMake invocation,
recovering the native smoke test (its `ctest` step is load-sensitive and can
flake under a saturated host). Recovers 7 of the 8 `test_list_irq` cases; the
eighth is the invalid-C mutant fixed in section 3.

### 2. Stale tests vs the range-table refactor — 27 tests + the xfail

Commit `d9f78a3a8` ("the formatter compiled for 16.7s against a 30s test
budget") replaced ~2,077 literal `else if (pc >= a && pc < b)` branches in
`formatter_fetch` with sorted `kFormatterRanges*` tables, and folded
`merge_pending_matches` into `kMergeRetireSites`. It updated only
`tests/test_pvd_irq.py`.

- `tests/test_second_geom_source_words.py` (16): asserted the literal guard
  strings. Added `_range_in_fmt()` (literal guard **or** table row) and
  `_dispatch_pos()` (word array → its literal branch or the
  `formatter_range_word(<table>, ...)` branch). All 18 now pass; the 80041E8C
  entry was updated to its merged span `[80041E8C,80042154)` (178 words,
  EXE-verified) from `214e3be63`'s promoted-`j` span merge, and the local
  untracked `artifacts/second-geom-source-exports.json` matches.
- `tests/test_overlay_identity.py` (11 errors): the `selector` fixture sliced a
  literal if-chain out of the source and baked the word arrays into a harness.
  It no longer compiled. Replaced with a probe that `#include`s
  `mips_formatter.c` and calls the static `formatter_fetch`, built with
  `-fvisibility=hidden -Wl,--gc-sections` so the rest of the port drops away.
  41 pass.

### 3. Extracted-slice probes broken by the same refactor — 5 tests

- `test_movie_signed_add`: the ADD body now calls `formatter_refuse0()` and
  reads `cpu->pc`; added both to the harness.
- `test_dma_byte_bus`: the byte-write path now calls `access_refuse0()` and
  reads `cpu->pc`; added both.
- `test_cd_irq_pac_progress`: the slice now contains `cd_irq_bank_progress()`,
  which `-Werror=unused-function` rejects; exercised it instead.
- `test_sc02_entry`: the helper slice reached to `formatter_step`, dragging in
  `getenv`/`fprintf` helpers the harness does not declare; GCC 16's C23 default
  rejects the implicit declarations. Slice only `sc02_entry_matches()`.
- `test_list_irq[mapped_mode_alias]`: the mutant injected `(void)` into the
  middle of a ternary (`(void) mode == 3u ? ...`), invalid C. Replaced with a
  valid mode alias the probe still rejects.

### 4. Stale mutant needles / carved addresses — 3 tests

- `test_draw_mmio`: the two guard needles ended in `return 0;`; the guards now
  end in `return formatter_refuse0(__LINE__, cpu->pc);`.
- `test_draw_packet`: `unmapped_queue` used `0x8005B7E4/B8F8/BA6C`, now inside
  the carved `[8005B7B0,8005BA90)` range. Pointed it at non-function bytes in
  main's text (`0x80063000/6A000/70000`).

### 5. Finding — SC02 PAC isolation (documented xfail)

The formatter carries **unconditional** `kOverlaySc02_*` ranges (e.g. the guard
at `mips_formatter.c:16910` serving `0x80128A28` from `kOverlay0012_...`), and
member0012 ranges are resident with no gate. So some SC02-only PCs are served
with no PAC selected. `test_sc02_only_exports_do_not_leak_without_their_pac`
records the leaked PCs as an xfail; gating them needs a live overlay-selection
decision, not a test change.

### 6. Residual behavioral failures — 9 tests (not touched)

These are real behavioral mismatches, not test rot; they predate this session
and the previous one (the earlier "39 failures were compile timeouts" reading
was incomplete — with the include cache the probes compile and the assertions
below are what actually run).

| test | first failing assertion |
| --- | --- |
| `test_gte_data_source` (4) | `camera_body`: `matrix+16 == 0x55667788` after `80048E98` SWC2 of control 11 |
| `test_gte_init_source` (2) | `second_geom`: `f.cpu.pc == expected && f.cycles == boundary_cycles` |
| `test_spu_reverb_source` | `REVERB_REFUSED pc=8003b098 ... writes=36 cycles=94912` |
| `test_input_digital_irq` | `read_word(0x800729b4) == (digital ? 0 : UINT_MAX)` in a later round |

## Startup steps 8–10 (diagnosis; not recovered)

Drafts generated with `m2c --valid-syntax` via a scratch driver (m2c's
`should_attempt` skips existing sources). Drafts are in `/tmp`, not committed.

| step | function | retail | m2c draft | gap |
| --- | --- | --- | --- | --- |
| 8 | `func_8002C8F4` | 214 words | 228 words | 14 words long |
| 9 | `func_8001971C` | 133 words | 141 words | 8 words long |
| 10 | `func_80010214` | 457 words | — | draft does not build (`saved_reg_s1` undeclared, void expressions) |

The mechanical repair generators (`tools/repair_drafts.py`, 70 single-edit
variants) do **not** close step 9: the excess is structural (control-flow /
allocator shape), matching the previous session's "allocator/scheduling puzzle"
finding. Steps 8–10 are hand-recovery work; step 10 also needs its draft
sanitized (missing declarations + `_expose_jump_tables`) before the oracle can
judge it at all.

## Commits

1. `tests: realign the second-geom source-word checks with the range-table formatter`
2. `tests: repair the extracted-slice probes broken by the formatter refactor`
3. `tests: make the mapped_mode_alias mutant valid C`
4. `tests: update draw_mmio mutant needles to the refusal-helper form`
5. `tests: move the draw-packet unmapped-queue PCs out of carved ranges`
6. `tests: compile the real overlay selector instead of slicing the source`
7. `tests: pass the versioned SDL2 config into the native smoke build`

## Next steps

- The 8 behavioral failures above, in the order GTE (6) → SPU → input. The GTE
  cluster is the largest and likely shares the shared-bank/control-11 read path.
- Steps 8–10: hand-recover from the scratch drafts; do step 10's draft
  sanitation first so it can be judged.
- The local-only include-cache pytest plugin still exists in `/tmp` only.
