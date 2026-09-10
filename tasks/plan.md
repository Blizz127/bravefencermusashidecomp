# Plan 4 — wrap the port, then scale matching

## Current continuation — native menu boot

The native run now completes retail display setup through the actual GP1
05/06/07/08 writes and returns through `8005279C`, with its 20-byte display
cache equal to the source DISPENV. Both the controller and real PsyCross adapter
own origin `(0,0)`, H `[608,3168)`, V `[16,256)`, mode 1, divisor 8 and 320×240.
The next unsupported entry is `80053CF8`, with RA `80052618` and SP `801FFF48`,
at BIOS/GTE initialization. **Menu: NOT_REACHED; display remains disabled.**

The new checked descriptor derives width from the horizontal video-clock range
and selected mode, preserving the real transient 256-pixel state before mode 1
selects 320 pixels. Reset restores 256×240. GP1 buffer reset preserves display
registers; GPUSTAT reflects accepted mode bits. The adapter validates raw and
derived fields, ownership and actual queued work before updating `activeDispEnv`
and `currentDispEnv`. Refused commands cannot publish source cache writes.
Supported modes are 0/1/2/3/40, NTSC progressive 15-bit, with the existing fixed
V `[16,256)` timing profile. Other modes/windows and enabled scanout still refuse.
No display setter clears VRAM, invokes a substitute SDK call, or presents a frame.

The preceding real DMA2 transfer remains intact: one header and six ordered GP0
commands reach PsyCross, complete at the declared device deadline, and return
through the source queue with `v0=0` and `I_MASK=0D`. E2..E6 drawing-register
ownership, inclusive bounds, signed offsets, raw info latches and accepted-prefix
accounting are retained. Timing remains the declared native reference model;
physical GPU/FIFO/raster timing and hardware parity are unproven.

Validation so far: 38 GPU controller tests pass, including all 256 mode encodings,
refusal and reentry boundaries. Three source tests execute the actual display
instructions and cache copy, cover four refusal prefixes, and reject compiled
store mutations; their Clang ASan/UBSan probe passes. The fresh full regression
passes 957 tests plus 92 subtests in 521.76 seconds. All 22 graphics tests, 11
headless tests and symbol checks pass. The earlier shared fixture initializer
failure is fixed; its failure log remains in the previous checkpoint. Independent
source/owner/native review accepts this bounded display milestone.

Current native evidence: `artifacts/spu-startup-20260906/native/gpu-registers-final/`.
Aggregate verification: `artifacts/spu-startup-20260906/gpu-register-verification.json`.
The immutable `gpu-display-verification.json` retains the prior GP1(05) refusal;
`draw-verification.json` retains the earlier no-DMA boundary. Existing 18 source
streams remain 1147 EXE/assembly-exact exported words (1047 mapped). These exports
do not claim newly matched C, full BIOS parity or a complete decompilation.

Next: execute the real BIOS exception-prefix patch and FlushCache publication,
then initialize persistent CP0/GTE state through source instructions. The
source audit identifies 108 additional words and 12 CTC2 writes; these are not
yet bound. See `gpu-gte-init-source-plan.md` and the CP0 startup authority follow-up
in the artifact directory. The audit corrects the earlier short plan: controls
21–23 are far color, not background color. Enabled scanout, actual title/menu
assets and primitive rendering, launcher and human acceptance remain open.

The completed Plan 4 below is retained as history. The immediate user priority
is the real retail menu booting in the native port, with Monday as a stretch
target, not an acceptance waiver or promised delivery date. The full decomp,
port, launcher integration, and separate runtime acceptance goal remains open.

Assumption: the native port continues to consume decomp-owned game code. An
emulator launch, asset viewer, replacement menu, or success-returning stubs do
not satisfy this milestone. Existing dirty work is preserved; this continuation
does not request a commit or push.

### B0. Establish the real entry contract (static audit complete)

The EXE enters at `80010000`, not `80010178`. Fresh byte checks, startup memory
effects, and direct-call coverage are recorded in
`docs/NATIVE-BOOT-ENTRY.md`. Static evidence is not runtime execution.

### B1. Bind the retail entry data to native storage

Dependencies: B0. Scope: medium, platform boundary plus focused tests.
Before implementation, review the storage contract: one backing store must
preserve overlapping retail globals; guest address words must not become
truncated host pointers. Ordinary RAM must not silently stand in for MMIO.

Acceptance:

- Load the pinned EXE data and reproduce the entry's observed clear range and
  heap-bound writes; use a native stack, not the retail stack address.
- Reject wrong identity, invalid spans, and unsupported address classes;
  verify overlapping views share bytes and surrounding sentinels survive.
- Keep this explicitly an entry-data test until the game startup is invoked.

Verification: focused native tests with negative controls, the existing CMake
build/CTest suite, and `python3 -m pytest tests -q`. Likely files: a platform
storage implementation/header, focused C test, CMake, and entry-contract doc.

### B2. Execute the recovered startup prefix

Dependencies: B1. Scope: medium per landed prefix, not the whole call graph.
Start with the once guard and matched `80043060`; advance in retail call order
to `800141F0`. Review how decomp symbols bind to B1 before changing them.

Acceptance:

- Native execution consumes decomp-owned code with shared retail state, not
  separate hand-written copies of the game routines.
- Compare resulting memory and call order with retail evidence; an unresolved
  callee stops the diagnostic at its address rather than returning success.
- Keep the full `80010178` mixed-assembly draft out of native builds.

Verification: focused prefix execution tests, original byte-match gates for
changed matched sources, and the full regression suites. Likely files: prefix
harness, symbol bindings, CMake, test, and entry-contract documentation.

The native entry now executes CRT, constructor, graphics, InitCARD, StartCARD,
backup-unit initialization, eight BIOS event registrations, and input setup on
one source CPU. Input C0:03/C0:02/C0:0A services and the two IRQ-register writes
match the pinned retail observation. The game input descriptor precedes the
actual BIOS SIO owner; its source verifier and handler use a dedicated 112-byte
BIOS scratch frame `[8568,85D8)`. The optional serial path executes five exact
SIO configuration writes around a Timer2 sample before refusing its unknown child; it is not a
natural controller transaction. Unknown child calls retain their effects and
refuse.

Input setup returns naturally at `800101E4`. CD initialization then prints
`CD_init:addr=8006cf68`, installs its callback, and stops at the first unbound
CD byte write, `80044DBC -> 1F801800` (bounded status `0`, executable exit `2`).
I_MASK and game enabled bits are `000D`, guest IRQ is enabled, and the input
owner/frame are healthy. The observed five VBlank deliveries preceded input
registration: no natural input IRQ ran in this short native or retail window.
The menu remains **NOT_REACHED**. Full CPU, cycle, low-RAM, hardware, and BIOS
cold-boot parity remain unproven; the executable loads the pinned EXE via host
`fread` and never executes retail-file code bytes.

See `docs/MENU-BOOT-CONTINUATION.md` for evidence and the current CD/input
handler dependencies. The source-authoritative three-boot CD contract is
`artifacts/cd-init-device-20260905/contract.md`; the source ledger accounts for
startup/input instructions while the paced host-time device epoch advances
Timer2 from actual host-time cuts with variable phase. `read16` does not advance
Timer2. CD and video deadlines remain disconnected. The clock contract and
negative controls are pinned in
`artifacts/clock-epoch-20260905/integration-contract.md`.

The current controller stage binds the native digital port-1 SIO owner to that
epoch and an SDL keyboard provider. Six metadata edges are mapped and four new
metadata arrays are integrated; startup still reports zero keyboard polls and
no DATA-pad packet. The legacy 16-bit `F830` path remains fail-closed at
`8005DB04`. The bounded contract and source/runtime evidence are recorded in
`artifacts/controller-protocol-20260905/integration-contract.md`.

### Checkpoint B — actual startup prefix execution

Review native runtime evidence and the first unresolved call before expanding
the next slice. Build/link success and source counts cannot pass this gate.

### Subsequent milestone gates (decompose after Checkpoint B)

1. Continue initialization through its required graphics, audio/input, and disc
   dependencies; establish retail-versus-native startup observations.
2. Follow the genuine loader/dispatcher into the menu overlays using retail
   assets and address-safe callbacks. Do not inject a menu state to skip boot.
3. Observe the actual menu on screen and verify input responsiveness.
4. Launch that same executable through a usable desktop/start-menu entry and
   verify it again. Keep human-visible acceptance distinct from automated tests.

The first two gates span unresolved call graphs, so they are not represented
as small implementation tasks or assigned speculative completion percentages.

## Historical Plan 4

Plans 1–3 are complete (retail registration through PAC extraction). This plan
answers Checkpoint P and Checkpoint A in one stroke: the port stops at an asset
viewer until decompiled game code exists to host, and decompression stays
unexplored until a chunk type is shown to need it. Effort then moves to
matching, which is the long pole.

```
[W1] viewer takes any TMD ──→ [W2] find TMDs in chunks ──→ [W3] status docs
                                                                  │
[D1] regenerate disassembly ──→ [D2] batch harness ──→ [D3] sweep ──→ [D4] one substantive hand match
```

## Phase W — port wrap-up (bounded)

### W1. The viewer renders any extracted TMD
`render_tmd` grows `--model PATH`, keeping the pinned model as the default so
ctest is unchanged. Rotation continues across frames so a viewer can see all
sides.
*Acceptance:* ctest `render_tmd` still passes; a second extracted TMD renders
with `--model` and `--screenshot`.
*Verify:* ctest, plus one manual screenshot of a different model.

### W2. Locate TMDs inside PAC chunks
`tools/find_tmd.py` scans an extracted chunk for candidate TMD headers and
keeps only those `tmd.py` parses cleanly to the end. This links A2 to P2: from
archive to screen through tools alone.
*Acceptance:* unit-tested on synthetic chunks; finds the P2 model in member 37
chunk 0 at `0x8800`; refuses false positives.
*Verify:* `python3 tools/find_tmd.py extracted/pac/sc01/0037_000.bin`.

### W3. Status docs
`docs/PC-PORT.md` gains a status section: what runs, what does not, and that
Windows is unverified here because no MinGW toolchain is installed. Checkpoint
P is recorded as decided.
*Acceptance:* a reader can run every target from the docs alone.

### ✅ Checkpoint W — port paused as a viewer; move to decomp

## Phase D — matching at scale

### D1. Regenerate the disassembly
`asm/` is untracked and was found empty. Regenerate from
`config/splat.template.yaml` against the pinned executable and record the
exact command in `docs/MATCHING.md` so this never costs a session again.
*Acceptance:* every function in `provenance/matches.json` re-verifies through
the oracle against the regenerated tree.

### D2. Batch harness that cannot destroy work
`tools/batch_match.py`: for each function, m2c → build → oracle in a scratch
directory. It **refuses** to write a path that already exists under `src/`,
promotes only exact matches, and appends to `matches.json`. The overwrite
incident in `docs/MATCHING.md` is the test case.
*Acceptance:* unit tests for refuse-to-overwrite, promote-on-match, and
discard-on-mismatch; no child without `stdin=DEVNULL` and a timeout.

### D3. Sweep the main executable
Run D2 over every function splat emits. Commit the matches with the
trivial/substantive split from `progress.py`.
*Acceptance:* `progress.py` reports more substantive matches than 3; every
new entry re-verifies.

### D4. One substantive hand match on the boot path
Pick the first non-trivial function on the entry chain (`main` or the overlay
loader) that the batch failed on. Decompile by hand, iterate against the
oracle, commit the match with notes on what m2c got wrong.
*Acceptance:* oracle exit 0; `docs/MATCHING.md` records the idioms learned.

### ✅ Checkpoint D — report the match rate; decide whether to keep sweeping or target the boot path

## Conventions
- RED before GREEN; one commit per task; stage only that task's files.
- Every child process: `stdin=DEVNULL`, timeout.
- Addresses and formats come from bytes, never from notes.
- Retail-derived data (asm, extracted, models, chunks) stays untracked.
- A build is not a match. Only the oracle says match.
