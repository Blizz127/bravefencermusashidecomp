# Session plan — bank the in-flight C recovery, extend portable C coverage (2026-09-18)

Goal: lock in the uncommitted recovery work on this branch, re-earn the
registry, then grow the **portable C-only** subset — the number that predicts a
native build, per `docs/PORT_GOAL_AND_PLAN.md`.

Additive: `tasks/plan.md`, `tasks/todo.md` and `tasks/plan-60-percent.md`
remain in force and were not modified.

## What was verified

- `python3 tools/verify_registry.py` — **2,730/2,730 re-verified, exit 0**
  (2,729 before the new match was registered).
- The 80 uncommitted registry rows were independently re-earned as a subset
  (80/80 MATCH) before being committed.
- `python3 tools/progress.py` at session close:
  - qualifying coverage **257,868 / 806,272 = 31.98%**
  - portable C-only **176,324 / 806,272 = 21.87%**
- `cmake -S . -B ... -DMUSASHI_BUILD_PC_PORT=ON` — configure exits 0
  (134.6 s; every carve `--expected-words` extraction passed).

## Commits made

1. `progress: report the portable C-only subset beside qualifying coverage`.
2. `matching: bank 80 repaired drafts and lift 80043300 from asm to C` —
   80 oracle-verified drafts (9,460 B, all complete C functions),
   `tools/repair_drafts.py`, the `docs/MATCHING.md` idiom catalogue, two
   improved near-miss drafts (8003E248 31->36/39, 80153D7C 27->28/33). The
   `func_80043300` conversion moves 152 B from assembly to portable C.
3. `matching: recover the boot-path leaf func_80046564 as C` — startup-chain
   rank 7e; a volatile local pointer reproduces the 6/6 shape, recorded in
   `docs/MATCHING.md`.
4. `port: third carve batch, RAM-mirror probes, GTE bank/control sites` —
   the prior session's in-flight work: symbol_addrs `.auto` lists, refreshed
   CMake entry range table + three sc02_0031 word extractions,
   `pc_port/gte_owner.c` read_data allow-list and read_control 9 refusal,
   KUSEG 8 MB RAM-mirror probe corrections, and the new
   `tests/carve_site_probe.c` / `tests/test_carve_sites.py`.

## What the automation says (negative results, recorded so it is not retried)

- `batch_match.py --register-existing --max-size 100000` across all three
  regions: 1,235 on-disk unregistered sources, **0 new matches**.
- `repair_drafts.py --depth 1` over the 30 drafts closest to retail: **0
  repaired**. The mechanical generators are exhausted; the residual
  near-misses are allocator/scheduling puzzles.

Closest residual drafts (missing words / total): 80154ED8 1/49 (needs the
`move a1,a2` call-delay-slot word gone without changing the two-argument
body's `a0/a2` shuffle), 801508F8 2/21, 8003EAB4 3/63, 8003E248 3/39,
8017385C 3/30, 8003EBB0 3/24, 80035210 4/24 (`$v0` vs `$v1` temp).

## Test-suite status (this host, 2026-09-18)

The repository is **not green**, independently of this session's changes.

- Current tree: **40 failed, 2,452 passed, 11 errors** (94 subtests).
- Same tree with the carve batch stashed: 44 failed, 2,447 passed, 11 errors.
  The batch therefore **fixes four tests and introduces none**.
- The failures predate the batch: `test_gte_init_source.py` baseline fails
  with `pc_port/gte_owner.c` reverted to HEAD, and
  `test_second_geom_source_words.py` fails on `src/main/80041e8c.c`, a file
  no session commit touched (expects 94 word macros, file has 178).
- The 80-promotion commit changed no word-export macro (10 files differ only
  by hex case), so it cannot affect the source-word tests.

To make the suite runnable on this loaded host at all, the 3,545 generated
word includes from `_generate_formatter_includes` were prebuilt once into
/tmp/bfm_inc_cache and served by a local-only pytest plugin; without it the
suite needed hours (183 tests in 22 minutes). That plugin is not committed.

## Next steps

- Diagnose the 40 pre-existing failures (do not assume they are environmental;
  the GTE/SPU/draw guard refusals look behavioral).
- Continue the startup chain in `docs/NATIVE-BOOT-ENTRY.md` rank order
  (step 8 `8002C8F4`, step 9 `8001971C`, step 10 `80010214`).
- Target the residual draft bank by fewest differing words rather than
  sweeping; the ranking method is in this session's history.
