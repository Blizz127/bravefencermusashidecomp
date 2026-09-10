# Todo — plan 4

## Current priority — real native menu boot

### Current mounted CD continuation — 2026-09-06

- [x] Complete source digital port1 polling, absent-port2 timeout and fixture
  `43` retry/recovery, with 256-byte scratch/eight returns/16384 instructions.
- [x] Mount pinned immutable disc data and connect the owned CD command/FIFO/
  IRQ lifecycle to the shared device clock and source interrupt handler.
- [x] Bind GPUSTAT/Timer1 word reads, COMMON_DELAY, and the real SDL/SPU CD path.
- [x] Complete the natural PVD, Type-L path-table, root-directory and LIST
  archive path through source return `80010204`, stopping naturally at `80010214`.
  The E40 LIST payload is 3648 bytes with retail-exact SHA-256
  `9acd715d059f94ae42126e76aa37e1eb747d2161fdf3fd3cd347a257c2ff7b42`; the
  following 448 unrequested bytes remain unchanged, and independent checks verify
  all 447 records/3129 defined metadata bytes against the pinned disc.
- [x] Verify 38 file/CD streams and 2855 EXE-exact words; pass 821 pytest tests
  plus 84 subtests, 21/21 graphics and 10/10 headless CTests, with symbol checks
  passing. See `artifacts/spu-startup-20260906/list-verification.json`.
- [x] Continue the live source through BIOS InitHeap, preserve its real register
  result and source critical-section return, then mode1 ResetGraph, disabled
  display, VSync and the render-state clear. Historical stop: `800143AC`.
- [x] Verify the four new source streams (510 words), 24 heap continuation
  cases, 12 graphics dispatch cases, and eight selected-ROM interpreter cases.
- [x] Continue `143AC -> 145EC -> 525DC`, produce the retail seven-word draw
  packet, and execute actual GPU direction2 selection. Historical stop: `8005B730`
  before MADR acceptance (draw-verification.json retains this checkpoint).
- [x] Verify15 draw streams/835 exported words (735 newly mapped), six focused
  tests,22 graphics/11 headless CTests and symbols. Full regression:849 pytest
  tests plus92 subtests; final retained-log checker separately passes24 tests.
- [x] Implement general bounded linked-list DMA2 with real ordered GP0 delivery,
  deferred reference-model completion, shared CHCR/IRQ and truthful partial faults.
- [x] Own E2..E6 raw drawing registers and real PsyCross configuration, including
  inclusive bounds, signed11 offsets, mask flags and latched info queries.
- [x] Verify actual native six-word DMA completion and source queue return;
  execute312 more exact source words through the GP1(05) refusal at8005B690.
  Historical stop: word05000000, RA8005A088, SP801FFEF0; menuNOT_REACHED.
- [x] Pass22 graphics/11 headless CTests, symbols and focused owner/source tests.
- [x] Collect full regression (933 passed/92 subtests; ten fixture compile failures),
  repair the shared initializer, and pass54 targeted tests including44 checker
  cases. Independent retained GPU/DMA review accepted; failure log preserved.
- [x] Pass the fresh display-register regression:957 tests plus92 subtests,
  22 graphics tests,11 headless tests and symbols; independent native review accepted.
- [x] Implement real GP1 05–08 display ownership and source cache return5279C;
  native controller/backend320×240 agree. Current stop53CF8, RA52618, SP801FFF48.
- [ ] Bind the source BIOS exception patch/FlushCache and persistent CP0/GTE initialization.
- [ ] Implement enabled VRAM scanout from actual source-produced pixels.
- [ ] Complete draw/display initialization from `143AC -> 145EC -> 525DC`,
  load the actual title/menu assets, and reach a working retail menu and launcher.
- [x] Complete the heap checkpoint regression: 828 pytest tests plus 92 subtests,
  22 graphics and 11 headless CTests, symbol checks and ASan/UBSan pass.
  See `artifacts/spu-startup-20260906/heap-verification.json`.

Current source/evidence: `docs/MENU-BOOT-CONTINUATION.md` and
`artifacts/spu-startup-20260906/`. The boot-entry 10,000,000-step inspection
policy has explicit retained 1,000,000-step quota proof. Progressive VSync remains
conditional on actual source/GPU state, with interlaced `XOR` unsupported. Hardware
timing, audible game/menu output, and parity remain unproven.

### Historical milestones and former next steps

The list below is retained context; current outstanding work is listed above.

- [x] Observe 600 normal retail slot-seven callbacks with the bounded request
  observer: initial index `FFFFFFFF`, no request call, black 320x240 frame.
  The corrected observer exits 2 at its limit; this is not menu evidence.
  Details and hashes: `docs/RETAIL-RUNTIME-BASELINE.md`.
- [ ] Next IRQ slice: bind the shared `800427F4` dispatcher with checked device
  acknowledgement, live callback loads, resampling, and explicit BIOS context
  return. Keep nonempty request targets unresolved; the bounded retail window
  supplied none. Direct child invocation must not stand in for IRQ delivery.
  - [x] Compile shared dispatch into the native library; synthetic IRQ state
    drives acknowledgement, live slot lookup, the real `80042CE8` child, and
    rescan. Retain 122/122 retail words. Stop with explicit result 2 before
    `8005CED8` when no platform provider exists; a provider can return explicit
    result 3 after accepting the BIOS return, which is not interrupt success.
  - [x] Recover B0:17 thunk `8005CED8` (3/3 words) and expose an explicit
    provider for the platform exception-frame return. The provider receives no
    game saved-record shortcut; delegated return is distinct from boot success.
  - [x] Add a single-owner PsyCross VBlank scheduler boundary. Its B0:19 hook
    receives the observed guest context through separate scheduler state, and
    its checked event provider drives the shared parent/child IRQ chain only
    in a test-owned VBlank source. A refused event is not counted as delivery.
  - [x] Route the recovered post-entry startup driver's real B0:19 call into
    that scheduler boundary. The live startup fixture observes installation
    with context `8006BB34` and zero injected deliveries; it does not force
    the unrecovered parent-IRQ guard merely to produce a frame.
  - [x] Observe a real PsyCross VBlank thread delivering the scheduler's
    synthetic checked IRQ fixture through `800427F4 -> 80042CE8 -> B0:17`.
    This confirms the event source only; it is not a game-startup delivery.
  - [x] Run the recovered callback initializer against the pinned EXE under
    PsyCross, let it set `8006BAFC`, and observe its B0:19 scheduler handoff
    reach the live shared IRQ chain without manually setting that guard.
  - [x] Replace the live probes' private IRQ-register storage with the native
    `I_STAT`/`I_MASK` controller. PsyCross VBlank now raises bit zero through
    production code and the recovered dispatcher acknowledges it through the
    same checked device; unknown callback targets remain fail-closed.
  - [x] Construct that controller and scheduler from the native entry owner;
    bind DPCR/DICR, the observed timer mode, and auto-ack policy. The real
    registration sets its guard/slots and I_MASK=0009 before the A0:72 stop.
    This uses bounded diagnostic frames and delivers zero IRQs in this run.
  - [x] Own the native BIOS CD session through the shared 22-record event pool
    and priority registry; A0:72 closes five owned events and unlinks two
    owned nodes while preserving game RAM and unrelated registrations.
  - [x] Run the cleanup gate through the owner pump at live FormatterCpu
    checkpoints; the worker only queues/coalesces VBlank edges and consumes the
    recovered B0:17 continuation. Cold-prefix deliveries remain zero.
  - [ ] Implement the actual BIOS CD-handler execution path; keep it
    fail-closed if reached. Supply production HBlank timing and GPU services
    before claiming startup continuation. Current evidence:
    `docs/MENU-BOOT-CONTINUATION.md`.

- [x] Historical graphics gate returned from `800141F0` with status 2 at the
  diagnostic sentinel (`pc=00000000`, `target=FFFFFFFF`); the first eight
  GPU writes match the retail trace. Query-7 leaves `GPUREAD=400`, while
  physical GPU revision, geometry, VRAM transfer, enabled scanout, and HBlank
  production input remain open. Evidence:
  `artifacts/gpu-startup-20260905/retail-run1/manifest.json`.
- [x] Continue the returned outer startup through `800101CC -> 8005FC68`,
  CD-first `B0:5B`, InitCARD, and post-init SYS2/SYS1 wrappers. The earlier
  event milestone opened/enabled/tested eight records and stopped at
  `8005D8D8 -> 8005E178`; its handles, BU flags, five VBlank-driven
  maintenance calls, and five game IRQ deliveries/ticks are historical
  evidence. The current native check continues to the first CD byte write at
  `80044DBC -> 1F801800`.
- [x] Capture and bind native input C0 kernel ownership, guest descriptor next,
  full timer-policy exchange, and exact 26/91-word callbacks on a dedicated
  BIOS scratch frame. Natural input setup returns at `800101E4`; raw input
  RAM/service/MMIO comparison passes. No natural input IRQ ran in this window.
- [ ] Implement the first CD byte register/device path at
  `80044DBC -> 1F801800`, then continue command, interrupt, data and menu
  loading behavior. The source-authoritative three-boot capture contract is
  `artifacts/cd-init-device-20260905/contract.md`.
- [x] Integrate the paced Timer2 owner after the optional serial path's five
  exact SIO writes, driven by checked source advance and actual host-time
  device cuts; `read16` does not advance it. The legacy 16-bit-only path
  refuses the call to `F830` at `8005DB04`.
- [x] Bind the digital port-1 SIO owner to the paced device epoch and SDL
  keyboard provider; map the six metadata edges and four new metadata arrays.
  Startup still reports zero keyboard polls and no DATA-pad packet, while the
  legacy 16-bit `F830` path remains refused at `8005DB04`. The byte-enabled
  real-source fixture reaches `DC04 -> EAE8`; full validation is 557 Python
  tests plus 84 subtests, 21 CTest checks and seven rejected compiled mutants.
- [ ] Exercise a natural keyboard/DATA-pad transaction and continue the CD path.
  The synthetic metadata fixture is not a natural controller transaction; the
  source ledger and paced device epoch remain separate, with no CD deadline.
- [ ] Supply production HBlank/GPU and SPU timing/ownership before claiming
  hardware or menu continuation. No menu or full CPU parity claim.

- [x] **B0 static audit** — verify the pinned EXE's actual entry, clear/heap
  effects, and first startup calls; see `docs/NATIVE-BOOT-ENTRY.md`.
- [x] Recover and register the startup constructor guard/loop
  `800100A0`: all 28/28 words match retail. The linker-resolved zero-count
  loop remains an assembly overlay and is not yet native startup execution.
- [x] Recover and register the two independent state-reset ranges
  `8005FC68` (12/12 words) and `8005FC98` (8/8 words); the older disassembly
  label grouped them as one 80-byte nonmatching block.
- [x] Recover and register `8005FCB8..8005FD18`: all 24/24 words match
  retail. Its following polling/helper range beginning at `8005FD18` was
  recovered separately below.
- [x] Recover and register the adjacent `8005FD18..8005FD58` state poll:
  all 16/16 words match retail.
- [x] Recover and register `8005FD58..8005FDD4`: all 31/31 words match
  retail. The larger handler beginning at `8005FDD4` remains unresolved.
- [x] Recover and register the startup retry/setup dispatcher `80043300`:
  all 38/38 words match retail. Its direct setup callees and native execution
  remain separate integration work.
  - [x] Execute its first retry probe `80043450(1)` as an exact guest slice.
  - [x] Compose the bounded post-entry driver through its genuine
    `800101E4 -> 80043300` call boundary with explicit retry/CD-register
    adapters; this is a returned diagnostic, not callback, native-boot, or
    start-menu proof.
    The `arg0 != 2` path first calls `80044D38`; a nonzero result returns one,
    while a zero result reaches the now-executed 61-word `80044BF4` leaf only
    when `arg0 == 1`. The leaf's checked guest-state/CD-command writes and
    `80043450`'s ready result are covered by the native boundary probe; do not
    collapse the still-unbound `80044D38` body into a guessed host readiness
    boolean.
  - [ ] Bind the success-path B0:7 calls from `80043398`, `800433C0`, and
    `800433E8` as three explicit requests: `(F0000003,20)`, `(F0000003,40)`,
    `(F0000003,40)`. Their surrounding callback-cell writes remain guest-RAM
    effects, not host callback registration.
- [x] **B1 entry-data boundary** shared byte storage, bounded cached-RAM access,
  pinned-image hashing, and entry clear/heap writes implemented. Native probe
  loads the actual EXE with explicitly synthetic incoming RA; whole-memory
  comparison and negative tests pass. This is not startup-prefix execution.
- [ ] **B2** execute the decomp-owned startup prefix against that storage;
  unresolved callees must stop explicitly, not be stubbed to success.
  - [x] Isolated matched `80043060` body consumes the shared word through an
    explicit scalar adapter; native state tests and the 6/6 retail word match pass.
  - [x] Bounded diagnostic connects the pinned CRT guard, matched exchange,
    and following write in retail order; stops before `800141F0`, reporting
    call-site `800101C0`. Full startup remains unimplemented.
  - [x] Exact-MIPS diagnostic enters `800141F0`, executes its first mode-zero
    ResetGraph call through formatter and callback-table dispatch, then stops
    at `80042598 -> 80042718`; later entry calls remain unreached.
  - [ ] Close `800141F0`'s first dependency, retail `80059234(0)` / ResetGraph:
    recover the correct 388-byte range and bind its guest environment effects.
    - [x] Recover and register `80059234`: all 97 words match retail.
      - [x] Execute its mode-5 exact-MIPS prefix through the environment clear
        and the `80042580` guest-table wrapper, stopping fail-closed at
        `80042598 -> 80042718`; callback initialization and all later
        ResetGraph work remain unbound.
    - [x] Recover and register `800594CC` console-state setter: all 25 words
      match retail; its BIOS formatter callback remains unbound natively.
    - [x] Recover and register adjacent `80059530` state-transition helper:
      all 43 words match retail; indirect callback boundaries remain open.
    - [x] Recover and register adjacent state readers `800595DC` and
      `800595EC`: both 4/4 words match at their 16-byte boundaries.
    - [x] Recover and register `800595FC` state setter: all 23 words match
      retail; its formatter callback remains unbound natively.
    - [x] Recover and register the remaining `800142C8` callees
      `8001903C`, `80029044`, and `8002906C`: all 10/10 words each match.
      - [x] Bind `8001903C` as a checked native composition over the
        `80016714` record clear; full `800142C8` callbacks remain open.
      - [x] Bind `80029044` and `8002906C` through checked RAM spans for their
        0x40- and 0x100-byte table clears; callback sequence remains open.
    - [x] Recover and register `80059658`: all 39 words match retail under
      `gcc-2.7.2-psx -O2`; native function-pointer/BIOS binding remains open.
    - [x] Recover and register `80016714` environment clear: all 41 words
      match retail under the observed `gcc-2.7.2-psx -O1` build.
      - [x] Bind through a checked cached-RAM span; native boundary tests cover
        aligned, unaligned, zero-count, overflow, and unsupported addresses.
    - [ ] Close its first call, the console path `8005C604 -> 8005C640`;
      PS1 argument words must not be passed as a host va_list.
      - [x] Recover `8005C388`: 45/45 words, isolated classification/tab/newline
        tests pass. It mutates the column word and calls a BIOS byte sink.
      - [x] Bind `8005C388` natively through a checked classification-table
        span, LE32 column word, and caller-owned byte sink; recursive output
        remains in the matched body. Formatter and BIOS remain unresolved.
      - [x] Recover and register the `8005CF38` BIOS write-vector thunk: all
        3/3 words match retail. Its native sink boundary remains separate
        because the thunk is a PS1 BIOS vector, not a host function call.
      - [ ] Bind the complete ResetGraph console path, including its actual
        `8005CF38` BIOS-vector destination; PsyCross's current write is
        unimplemented.
        - [x] Match the 15-word `8005C604` varargs wrapper. Retail saves the
          format and all three register words in its 24-byte PS1 frame before
          calling the formatter; the caller-area idiom is registered in
          `src/main/8005c604.c`. Fixed-argument drafts were 14/15 words.
        - [x] Recover the 121-entry analysis jump table from pinned bytes;
          correct raw decompiler width/argument/stack/zero-case errors in an
          ignored draft. Six scalar-format cases pass with ASan/UBSan.
        - [x] Recover `8005C640`: 418/418 words, including the complete
          jump-table-driven body. It is a source-backed instruction overlay;
          guest-pointer conversions and BIOS output remain unbound natively.
          Scalar draft probe passes 262,151 cases with Clang ASan/UBSan,
          including exhaustive short values for four integer conversions.
        - [x] Execute the exact `8005C604 -> 8005C640` streams against checked
          guest RAM and a caller-owned byte sink; literal, `%d`, and `%s`
          probes cover guest argument words and the wrapper home area. This
          remains below the `8005CF38` BIOS-vector and ResetGraph boundaries.
        - [x] Recover and register `8005CD18` string length: 12/12 words.
        - [x] Recover and register `8005CD48` fallback-string emitter: 20/20
          words; post-increment character load preserves retail delay ordering.
        - [x] Recover and register `8005CCC8` bounded byte search: 20/20
          words; combined initial guards and pre-decrement loop match the
          count-test layout. Success returns the matching byte's address.
          - [x] Link the unchanged source into the native port through
            `musashi_boot_search_bytes`; validate guest spans and translate
            results back to guest addresses, with boundary regression tests.
    - [x] Recover and register its low-level reset `8005BD7C`: all 87 words match.
      - [x] Bind its observed interrupt/MMIO/queue path through explicit native
        16/32-bit callbacks and checked shared-RAM spans; ResetGraph/backend
        execution remains open.
    - [x] Recover and natively bind `8005C29C` through checked RAM spans; all
      11 words match, and its actual reset fill/clear ranges pass native tests.
    - [x] Recover `80042580`'s indirect callback-init dispatch; all 12 words match.
    - [x] Recover and register `80042718`: all 55/55 words match retail.
      Bind its saved-context, callback-table installation, and interrupt/BIOS
      boundaries separately; the guest pointer overlay is not native code.
      - [x] Recover interrupt dispatcher `800427F4`: 122/122 retail words;
        native callback execution and BIOS return-context handling remain open.
      - [x] Bind shared C registration `800429DC` to checked guest RAM and
        explicit IRQ/B0:5B/C0:0A operations; retain its 85/85 retail match.
        The initializer diagnostic now installs slots 0 and 3 through this
        native body, with a missing-BIOS negative control. Device/BIOS
        providers remain synthetic; interrupt delivery and cold boot are open.
      - [x] Recover its word-clear helper `80042C64`: all 11 words match;
        0x41A words clear up to, but not into, the dispatch table.
        - [x] Bind it through a byte-backed checked RAM view; the full 0x41A
          clear and table sentinel pass native boundary tests.
      - [x] Execute the exact initializer through IRQ/DMA setup, clear, and
        the `8005CD98` register record with a three-register device adapter;
        stop at `800427A0 -> 8005CEF8` (`B0:19`) without a BIOS stub.
      - [x] With host-owned `HookEntryInt` and guest callback-registration
        adapters, execute exact `80042C90` through its `1F801114 = 0x107`
        write and index-zero `80042CE8` registration; the verified call is
        `jal 800427BC -> 80042DB8`.
      - [x] Execute exact `80042DB8` through its eight-word clear,
        `1F8010F4 = 0` write, and index-three `80042E08` registration; stop
        at the verified `jal 800427CC -> 8005CE50` (`A0:72`,
        `ra=800427D4`) without a BIOS stub.
      - [x] With explicit `_96_remove` (`A0:72`) and `SYS(2)` providers at the
        verified `jal 800427CC` and `jal 800427D4` sites, reach `800427F0`'s
        final return-transfer boundary; do not cross its final delay slot in
        the standalone diagnostic or claim caller/ResetGraph continuation.
      - [x] Integrate that return with exact `80042580` and ResetGraph; stop
        at `800592D4 -> 8005CE38` (`A0:49` GPU_cw), without a GPU BIOS stub.
      - [x] With an explicit GPU_cw provider, reach `800592DC -> 8005BD7C`;
        keep low-level device reset under its separate live-pointer contract.
      - [x] Supply that reset adapter and return through ResetGraph to the next
        startup boundary, `80014200 -> 800594CC`; no startup completion claim.
      - [x] Execute exact `800594CC(0)` and reach `80014208 -> 80059658`;
        retain its nonzero indirect callback as an unresolved separate path.
      - [x] Recover installer `80042C90`: 22/22 words. Interpreter disc boot
        observes guard initialization and both installed dispatch targets;
        see `docs/RETAIL-RUNTIME-BASELINE.md`. Native integration remains open.
      - [x] Recover returned DMA callback registration `80042F8C`: 42/42
        words. Replaced the assembly overlay with matched C and compiled its
        shared body against guest RAM and checked control-register operations.
        Eight-slot enable/disable, pointer aliasing, and refusal tests pass;
        DMA transfer and interrupt delivery remain open.
      - [x] Recover registration wrapper `800425B0` (12/12 words) and
        handler `80042CE8` (30/30 words); test live slot reads and counter wrap.
      - [x] Bind the shared `80042CE8` body to guest RAM. It increments the
        real tick and reads all eight slots live; missing/refused execution
        stops without skipping a nonzero callback. Direct invocation after
        initializer setup is tested; scheduled VBlank/IRQ delivery remains open.
      - [x] Observe normal retail VBlank dispatch through `800428D4` to
        `80042CE8`: first nonempty visit calls slot-seven `800616D0` and returns.
        Recover that callback and helpers `8006291C`/`80062988` in C with
        40/40, 27/27, and 4/4 exact retail word matches.
      - [x] Bind that observed callback chain to the native executor, retaining
        the live request-index re-read and unresolved request/completion targets.
        The event-startup probe installs slot seven and the idle index through
        recovered code, then directly runs the shared VBlank chain. IRQ delivery
        and binding nonempty request/completion targets remain open.
      - [x] Bind shared `800425B0` and `800425E0` dispatch wrappers, retaining
        both 12/12-word matches. Startup runners now invoke the recovered
        registration body through the live guest table; the former game-level
        registration hook is removed. Fixtures verify actual IRQ slots 0/3/2,
        enabled bits, previous callbacks, and refusal of unknown dispatch targets.
        Device/BIOS providers remain synthetic; menu boot is still open.
    - [x] Recover and register the mode-zero device query `8005C1C0`: all
      55/55 words match retail. Its MMIO reads/writes still need an explicit
      native device contract.
    - [ ] Bind shared environment aliases and close the callback/BIOS/device
      helpers; no native forwarding shortcut has been installed.
- [ ] **Checkpoint B** inspect runtime prefix evidence and next unresolved call.
  - [x] Execute `80044D38` through its checked console, callback, command,
    and first status-poll slices; the exact continuation reaches `80044250`
    with the live `80044124` frame intact.
  - [x] Extend that same guest CPU frame through
    `800441D8 -> 8005CD48 -> 8005C604 -> 80044B14`; retain the live
    `a1/a2/a3` formatter words, then stop at the first unbound transfer.
  - [x] Recover the exact `80044250` status/callback loop and execute its
    timeout return; bind its `800426D4` ready-status leaf from guest RAM.
  - [ ] Capture and resume the retry-exhausted `80044198 -> 8004424C`
    retail frame (counter is at least `0x003C0000`) before driving the
    `80044250` callback/status loop; do not treat focused fixtures as menu
    proof.
- [ ] Decompose the next initialization/overlay slice from that evidence.
  - [x] Execute the retail-observed `80043B9C` CD-status worker's no-command
    return from a 354-word tracked-assembly bridge; formatter/jump-table
    paths remain explicit boundaries until C recovery and retail inputs exist.
  - [x] Execute retail `jtbl_800737CC[0] = 80043F54` through that worker;
    verify its command-clear and published status byte without host routing.
  - [x] Execute retail `jtbl_800737CC[1] = 80043F08` through that worker;
    verify its retained command bytes and state-two publication.
  - [x] Execute retail `jtbl_800737CC[2] = 80043E08` with its zero `CD4C`
    table cell; verify the state-two return route.
  - [x] Execute retail `jtbl_800737CC[3] = 80043FD8` and
    `jtbl_800737CC[4] = 8004405C` through their zero-command return paths;
    extend the exact interpreter with retail `blez` semantics.
  - [x] Execute the worker's state-six default path through explicit
    `8005CD48` and `8005C604` adapters; retain it as a diagnostic fixture,
    not menu or CD-completion proof.
  - [x] Execute the positive-`CC90` worker path through both retail formatter
    calls and its state-five return; literal diagnostic fixtures do not stand
    in for live CD input.
- [ ] Actual retail menu rendered by native boot, with responsive input.
- [ ] Same executable launched through a usable start-menu entry.

The checked Plan 4 tasks below are historical. The full project goal remains
open; the menu milestone does not stand in for full retail parity.

## Phase W — port wrap-up
- [x] **W1** viewer fits any TMD from its vertex bounds; `--frames N` spins it; ctest unchanged
- [x] **W2** `tools/find_tmd.py`: 8 tests; finds 4 models in member 37 chunk 0, the P2 one at payload offset 0x87F0
- [x] **W3** `docs/PC-PORT.md` status rewritten: what runs, what does not, Windows unverified (no MinGW)
- [x] **⏸ Checkpoint W** — port paused as a viewer on 2026-09-03; effort moves to matching

## Phase D — matching at scale
- [x] **D1** `asm/` regenerated for main and both overlays; commands in MATCHING.md; `tools/verify_registry.py` re-verifies 25/25
- [x] **D2** `tools/batch_match.py`: scratch-dir only, refuses existing `src/` paths, promotes exact matches; 14 tests
- [x] **D3** swept main (168 matches) and main_0012 (58 matches); 251/251 registry entries re-verify; substantive count 225 (was 3)
- [x] **D4** `func_80010A98` matched by hand at -O0 (not the identified -O2 default); fixed two verify_registry bugs it exposed
- [x] **⏸ Checkpoint D** — 252 matches (226 substantive), report and hand off

## Standing constraints
- [ ] RED before GREEN; one commit per task; stage only that task's files
- [ ] every child process gets `stdin=DEVNULL` and a timeout
- [ ] formats and addresses observed from bytes, never taken from notes
- [ ] retail-derived data stays untracked
- [ ] a build is not a match; a match is not a compiler identification
