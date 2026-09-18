# Session plan — bank the in-flight C recovery, extend portable C coverage (2026-09-18)

Goal: lock in the uncommitted recovery work on this branch, re-earn the
registry, then grow the **portable C-only** subset (the number that predicts a
native build, per `docs/PORT_GOAL_AND_PLAN.md`).

This file is additive: `tasks/plan.md`, `tasks/todo.md` and
`tasks/plan-60-percent.md` remain in force and were not modified.

## What was verified

- `python3 tools/verify_registry.py` — **2,729/2,729 re-verified, exit 0**
  before the new commit, and re-run after it (2,730/2,730).
- The 80 uncommitted registry rows were independently re-earned as a subset
  (80/80 MATCH) before being committed.
- `python3 tools/progress.py` at session close:
  - qualifying coverage **257,868 / 806,272 = 31.98%**
  - portable C-only **176,324 / 806,272 = 21.87%**

## Commits made

1. `progress: report the portable C-only subset beside qualifying coverage` —
   the C-only meter, its tests, `docs/PORT_GOAL_AND_PLAN.md`, and the goal
   banner / status refresh in `PROGRESS.md` and `DEFINITION-OF-DONE.md`.
2. `matching: bank 80 repaired drafts and lift 80043300 from asm to C` —
   80 oracle-verified drafts (9,460 B, all complete C functions),
   `tools/repair_drafts.py`, the `docs/MATCHING.md` idiom catalogue, and two
   improved near-miss drafts (8003E248 31->36/39, 80153D7C 27->28/33). The
   `func_80043300` conversion moves 152 B from assembly to portable C.
3. `matching: recover the boot-path leaf func_80046564 as C` — startup-chain
   rank 7e (`docs/NATIVE-BOOT-ENTRY.md`) recovered 6/6 with a volatile local
   pointer; idiom recorded in `docs/MATCHING.md`.

## What the automation says (negative results, recorded so it is not retried)

- `batch_match.py --register-existing --max-size 100000` across all three
  regions: 1,235 on-disk unregistered sources, **0 new matches** (main 164
  build-failed / 420 mismatch / 4 refused word dumps; main_0007 5 build-failed;
  main_0012 221 build-failed / 421 mismatch).
- `repair_drafts.py --depth 1` over the 30 drafts closest to retail (ranked by
  fewest differing words): **0 repaired**. The mechanical generators are
  exhausted; the residual near-misses are allocator/scheduling puzzles.

Closest residual drafts (missing words / total): 80154ED8 1/49 (needs the
`move a1,a2` in the call delay slot removed without changing the two-argument
body's `a0/a2` shuffle), 801508F8 2/21, 8003EAB4 3/63, 8003E248 3/39,
8017385C 3/30, 8003EBB0 3/24, 80035210 4/24 (`$v0` vs `$v1` temp).

## Left uncommitted on purpose

The working tree still holds an in-flight **third carve batch** from the prior
session: `CMakeLists.txt` (expanded `MUSASHI_ENTRY_RANGE` table + three new
sc02_0031 word extractions), `config/*.yaml` (`symbol_addrs` auto lists),
`pc_port/gte_owner.c` (GTE read_data selector allow-list, read_control
selector 9 refusal), `docs/NATIVE-BOOT-ENTRY.md` (startup-chain ranking),
`docs/PC-PORT.md` (GPU seam decisions), and the matching probe/test updates
(`tests/gte_*_probe.c`, `tests/*_source_probe.c`, `tests/test_*.py`,
`tests/carve_site_probe.c`, `tests/test_carve_sites.py`).

It is **not committed because it could not be re-tested on this host**: the
focus test files call `_generate_formatter_includes`, which spawns one
`extract_asm_words.py` process per word include in `pc_port/mips_formatter.c`
(3,600 of them), and the host was under load ~9-10 from unrelated processes.
`tests/test_gte_init_source.py` alone ran >10 minutes without finishing.
Validate with the focused files (and `tools/run_tests.sh`) on an idle host
before committing.

## Next steps

- Validate and commit the third carve batch on an idle host.
- Continue the startup chain in `docs/NATIVE-BOOT-ENTRY.md` rank order
  (step 8 `8002C8F4`, step 9 `8001971C`, step 10 `80010214`).
- The residual draft bank is now ranked; target by fewest differing words
  rather than sweeping.
