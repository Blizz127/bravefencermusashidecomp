# Session record — vendor intake (2026-09-18)

Goal: "port and decompile more." Two strands, both landed.

## 1. Port: GTE control bank + camera CTC2 admission

`pc_port/mips_formatter.c`:

- The two light-matrix SWC2 stores (`80048E98` word `E88B0010`,
  `80048FA8` word `E8AB0010`) publish control register 11, but the SWC2 path
  read the data bank (MFC2 semantics). They now go through `read_control`;
  every other admitted SWC2 site still reads data. `MUSASHI_GTE_CONTROL_LIGHT_READ`
  is 11 and `musashi_gte_owner_read_control` already documented that this is
  the path stores must compose with a RAM write.
- The opcode-18 stale-RA bank profile shadowed the table's caller checks, so
  the camera branch CTC2 rows (table indices 13..22, the `gte_48d9c_caller` /
  `gte_484ec_caller` rows) were admitted with a wrong RA. Those rows are now
  excluded from the bank profile; the InitGeom CTC2 pair still admits by exact
  site. `tests/test_gte_data_source.py`'s mutation needles were re-pointed
  (two were stale; the DIV mutant was masked because the explicit site and
  `div_guard_present` each subsume the other, so it now breaks both).

Recovers `test_gte_data_source` (baseline, sanitizers, mvmva, swc2, div_site).
`test_gte_init_source`'s `second_geom` boundary case (which=2, expected
`80047CE8`, run continued to pc=0) is still open.

## 2. Decompilation: vendor intake promoted 278 functions

`vendor/bfm-decomp` is Druthulu's **matching** decompilation of the same USA
disc (SLUS-00726), and `docs/VENDOR-CLEANUP.md` already authorized intake:
extract, split to an address-named file, re-verify with the oracle.

Pipeline that worked:

1. Index every `vendor/bfm-decomp/src/**` `.c`/`.h` by the `func_XXXXXXXX(`
   names it mentions.
2. For each unregistered region function, find a file that *defines* it
   (brace-matched definition, not a prototype) and take the definition text.
3. Preamble = that TU's top-level `extern ...;` and `#define` lines. **Do not**
   prepend the TU's function prototypes: doing so changed codegen and dropped
   the main-region hits from 23 to 5.
4. Build with the pinned toolchain at `-O2` then `-O0`; keep the first exact
   (0 differing word) result. The vendor uses per-segment optimisation flags,
   and boot-adjacent main leaves are `-O0` while overlay bodies are `-O2`.
5. Write the dual-shape source (word export regenerated from the checked
   assembly, vendor body in the `#else`) and a registry entry with the winning
   optimisation, then run `tools/verify_registry.py`.

Results:

| Batch | exact / candidates | bytes |
|---|---:|---:|
| `main` (first-match index) | 23 / 326 | 4,576 |
| `main_0012` (definition-aware index) | 250 / 642 | 56,400 |
| `main_0007` (definition-aware index) | 5 / 5 | 2,036 |
| `main` (definition-aware, wider path cap) | 2 / 564 | 1,488 |
| **total** | **280** | **64,500** |

`tools/progress.py`:

- qualifying unique: 262,444 -> **322,368 / 806,272 = 39.98%**
- portable C-only: 180,900 -> **240,824 / 806,272 = 29.87%** (was 21.87%)
- `main_0007` is now fully recovered.

`tools/verify_registry.py`: 3,010 / 3,010, exit 0.
`tests`: 5 failed / 2,498 passed — the same pre-existing set as before intake
(`gte_init_source` second_geom x2, `input_digital_irq`, `spu_reverb`, and the
load-flaky native smoke).

## Open work

- `main` is only partly swept: the first-match index found 23 and the
  exact-stem-first index found 2, so the matching TU varies per function and a
  "try every mentioning file" pass is needed to avoid missing hits.
- ~540 `main` and ~390 `main_0012` candidates still score `build-failed` or
  `no-def`: those vendor bodies need their TU's local types/includes, not just
  the `extern` preamble. The next lever is carrying the TU's quoted includes.
- `-O1` was not tried (the registry has one `-O1` entry, so the oracle accepts
  it).
- `second_geom` which=2 is the last GTE-cluster behavioural gap.
