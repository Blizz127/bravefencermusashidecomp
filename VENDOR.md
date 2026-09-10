# Vendor BFM-decomp intake

Raw matched tree from [Druthulu/BFM-decomp](https://github.com/Druthulu/BFM-decomp)
(SLUS-00726, 100% match claim) lives at:

```
vendor/bfm-decomp/
  src/           # Druthulu layout: 800*.c, ov_*, md_*, shared/, resident/
  include/       # common.h, include_asm.h, psyq/
  config/        # symbols.us.txt, splat.us.exe.yaml, …
  LICENSE, README.md, THIRD_PARTY.md
```

Imported via rsync from `_refs/BFM-decomp` / branch `vendor/bfm-decomp`.
**Do not compile `vendor/bfm-decomp/src/800.c` wholesale into the PC port.**

## PC port wiring

- Default (`MUSASHI_USE_VENDOR_BFM=OFF`): `musashi_shared` links the existing
  house-style matched leaves under `src/main/800*.c` (address-named files).
- `MUSASHI_USE_VENDOR_BFM=ON`: same smoke symbols, still from cleaned
  `src/main/` sources (local form wins over Druthulu’s giant-TU / `__asm__("$0")`
  shapes). Requires the vendor tree to be present; sets
  `MUSASHI_USE_VENDOR_BFM=1` and records the symbol→file map for intake.

See `docs/VENDOR-CLEANUP.md` for how raw vendor C is cleaned into house style.
See `docs/PC-PORT.md` for smoke/native_boot build notes.

## Smoke symbol map (vendor → cleaned)

| VRAM       | Vendor (raw)           | Cleaned (pc_port)        |
|------------|------------------------|--------------------------|
| 0x80012AB0 | `src/800.c`            | `src/main/80012ab0.c`    |
| 0x80012E6C | `src/800.c`            | `src/main/80012e6c.c`    |
| 0x8001311C | `src/800.c`            | `src/main/8001311c.c`    |
| 0x80013154 | `src/800.c`            | `src/main/80013154.c`    |

Enable:

```sh
cmake -S . -B build -DMUSASHI_USE_VENDOR_BFM=ON
cmake --build build --target musashi_pc_smoke
ctest --test-dir build -R musashi_pc_smoke --output-on-failure
```
