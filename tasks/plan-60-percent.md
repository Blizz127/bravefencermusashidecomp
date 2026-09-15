# Plan 5 — decompile to the 60% byte-coverage checkpoint

Authority for "complete" is [docs/DEFINITION-OF-DONE.md](../docs/DEFINITION-OF-DONE.md).
This plan covers only the decompilation side up to the **60% checkpoint**
(≥ 483,764 / 806,272 bytes). The native port resumes after.

Plans 1–4 (`tasks/plan.md`) remain in force; this file is additive and does not
replace any unchecked task there.

## Where we are

| Measure | Value |
| --- | --- |
| Qualifying coverage | 235,688 / 806,272 = **29.23%** |
| 60% checkpoint | 483,764 bytes (need **+248,076**) |
| Reachable ceiling | 697,632 bytes (86.53%) |
| Unmatched functions | ~1,526 fns / ~458,308 B |

Automation is exhausted: a full `--register-existing --max-size 100000` sweep
of all three regions plus fresh sanitized `m2c` regeneration produced only 14
latent matches and zero new ones. The remaining work is manual C recovery
against the oracle.

## The unit of work: one function

Every function follows the same loop. It is `S`-sized and independently
verifiable; never batch-edit sources outside it.

1. Read retail disassembly: `python3 /tmp/batchshow.py REGION 0xADDR`.
2. Read the existing `m2c` draft and the oracle's first differing word.
3. Write matching C into the source's `#else` body; keep the `.word` export.
4. `python3 tools/trycand.py REGION 0xADDR FILE` until `MATCH`.
5. `python3 /tmp/diffcand.py REGION VRAM SIZE cand.bin` to fix codegen drift
   (operand order, strength reduction, branch delay slots, `slti`/`sltiu`).
6. Register exactly: `--register-existing` re-verifies and appends on MATCH.

Acceptance per function: `tools/match_function.py` MATCH, source carries the
verified header, registry row added.
Verify per function: the oracle, then `tools/verify_registry.py` at each
checkpoint.
Likely files: `src/main/NNNNNNNN.c` or `src/overlays/main_XXXX/NNNNNNNN.c`.

## Phases and checkpoints

### Phase A — baseline and latent wins (done, 2026-09-11)

- [x] Fix the Definition of Done.
- [x] Sweep every existing source at all sizes and optimization candidates:
      14 latent matches registered (+1,156 bytes).
- [x] Hand-match `func_8002F0D0`, `func_8001C044`.
- [x] Restore the dangling `src/main/8005e194.c` registry source.
- [x] `tools/verify_registry.py` green.

### Phase B — clear the 30% threshold (done, 2026-09-14)

- [x] Establish that the toolchain runs here: the SIGSYS failure is the
      command sandbox, not the host. `verify_registry.py` green from an
      unsandboxed shell.
- [x] Re-confirm on a working toolchain that the default-mode sweep is
      exhausted: 0 new matches across all 1,526 unregistered sources.
- [x] Fix the reason 1,220 drafts never reached the oracle: m2c now runs
      with `--valid-syntax`, `include/m2c_macros.h` supplies the macros, and
      `tools/recarve_drafts.py` re-carves only the drafts that fail to
      build. 579 rewritten; the same sweep then found **60 matches**.
- [x] Hand-match the word-dump and near-miss functions: the 20 `.word`
      dumps the classifier correctly refused, plus the drift catalogue in
      `docs/MATCHING.md`.
- [x] Register merged ranges for the seven spans where splat promoted a
      `j` target to a function symbol.
- [x] Checkpoint B: coverage **30.56%**, `verify_registry.py` exit 0 at
      2,530/2,530.

### Phase C — 40% (need ≈ +81,900 B from 30%)

- [ ] Continue the per-function loop across the 257–512 B tier.
- [ ] Document recurring idioms in `docs/MATCHING.md` as they are learned.
- [ ] Checkpoint C: coverage ≥ 40.00%, registry green, suites pass.

### Phase D — 50% (need ≈ +79,000 B from 40%)

- [ ] Push into the 513–1024 B tier.
- [ ] Checkpoint D: coverage ≥ 50.00%, registry green, suites pass.

### Phase E — 60% checkpoint (need ≈ +86,000 B from 50%)

- [ ] Finish the remaining large-function tiers.
- [ ] Checkpoint E (the goal): coverage ≥ 60.00%, `verify_registry.py` exit 0,
      full suites pass, `docs/PROGRESS.md` updated.
- [ ] Hand off to the native-port track (`docs/PC-PORT.md`).

## Risks and mitigations

| Risk | Impact | Mitigation |
| --- | --- | --- |
| Per-function codegen drift (operand order, scheduling) | High — blocks byte match | `/tmp/diffcand.py` side-by-side loop; record idioms |
| Unsymbolized data globals | Med — build fails | `derive_symbol_address` handles `D_XXXXXXXX`; else add a reviewed symbol |
| Metric inflation pressure | High — false 60% | DoD integrity rules; `verify_registry.py` gate; no bulk assembly |
| Context/effort exceeding one session | Certain | Work phase by phase; commit per batch; report the real number |

## Conventions

- RED before GREEN; one logical batch per commit; stage only that batch.
- Every child process: `stdin=DEVNULL`, timeout.
- Addresses and formats come from bytes, never from notes.
- A build is not a match. Only the oracle says match.
