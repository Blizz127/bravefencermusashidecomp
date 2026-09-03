# Milestone 0 evidence

Status: **scaffold complete; retail extraction gated**.

This report distinguishes implemented infrastructure from retail-derived facts.
No boot serial, executable address, executable hash, compiler identity, function
boundary, or matching percentage is claimed yet.

The repository intentionally remains uncommitted pending operator review. An
initial commit is the next provenance pin, but was not authorized as part of
Milestone 0.

## Acceptance map

1. **Isolated repository — PASS.** The repository is
   `/var/home/blizz/Projects/brave-fencer-musashi-decomp`. It has no remote and
   no commits. The dirty Xenogears checkout was used read-only; its status
   changed concurrently during this work, so no clean/unchanged claim is made.
2. **License-safe layout — PASS.** `.gitignore` excludes retail, disc,
   extracted, payload, build, CHD, BIN/CUE, ISO, executable, and common PS1 boot
   filename paths. Only source, tests, templates, documentation, and digests are
   present.
3. **Retail registration and extraction — PARTIAL / GATED.** The real CHD
   registration dry run verified size `210618433` and SHA-256
   `511e4bcae71bb09b5b7e4818aa303a6fa06c189a29dfdef55224a68d4e4150cc`.
   `tools/extract_retail.py --dry-run` stopped with exit 2 because `chdman` is
   absent. No extraction was run and no output was written.
4. **Matching-decomp skeleton — PASS AS SCAFFOLD.** The repository includes an
   unresolved executable identity record, a splat template, assembly/source
   layout, an `include_asm` boundary, and a compiler-identification contract.
   Population and byte matching remain gated on direct executable observation.
5. **Native boundary — PASS AS PLUMBING.** CMake builds `src/shared/runtime_api.c`
   into `musashi_shared`, links it through a platform adapter, and runs the Linux
   smoke executable. The Windows adapter is present but was not cross-built.
   This does not prove gameplay portability.
6. **Automated verification — PASS.** `tools/run_tests.sh` passed 11 Python
   tests, a clean out-of-tree CMake build, CTest `1/1`, and the Linux smoke run.
7. **Evidence-separated roadmap — PASS.** `docs/ROADMAP.md` separately defines
   static matching, emulator observation, native runtime, and human parity.
8. **Dependency decision — PASS.** No package or system mutation was performed.
   Installing or otherwise providing `chdman` is the next explicit gate.

## Reproduction

```sh
python3 tools/register_retail.py --dry-run
python3 tools/extract_retail.py --dry-run  # expected exit 2 until chdman exists
./tools/run_tests.sh
git remote -v                             # expected empty
git status --short
```

Observed native smoke output:

```text
musashi_pc_smoke: platform=linux frame=0 pad=0 le32=0x78563412
```

## Next gate

Provide a reviewed `chdman` executable without committing it, run the extraction
pipeline, inspect the generated BIN/CUE and filesystem view, then record the
`SYSTEM.CNF` boot target and PS-X EXE identity. Only those observed values may
replace the unresolved splat fields.

## Implementation lineage

Fable 5.1 orchestrated the milestone. GPT-5.6 Luna workers initially wrote the
root/decomp scaffold and native-port boundary, but their turns ended with
post-write OpenCode gateway HTTP 400 response-ID errors. Recovery turns verified
or extended the files and hit the same lifecycle error. The DeepSeek V4 Flash
test worker produced no files and was interrupted after stalling.

Codex inspected all landed files, corrected `.gitignore`, `README.md`,
`docs/ROADMAP.md`, `tools/extract_retail.py`, and
`tools/identify_retail.py`, and authored `tests/`, `tools/run_tests.sh`, and this
report. Codex then ran the real CHD registration/negative extraction gates and
the complete automated suite. This records implementation authorship only; no
worker lifecycle result is used as retail or matching evidence.
