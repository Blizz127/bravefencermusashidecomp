# PC port

The port links the decompilation against
[PsyCross](https://github.com/OpenDriver2/PsyCross) (MIT), which reimplements
the Psy-Q libraries for PC on SDL2, OpenAL and OpenGL. It is vendored at a
pinned commit by `tools/fetch_toolchains.sh` and its checkout is ignored.

## Status

Cleared REFUSED `800D18DC` (MAIN10 `[800D18DC,800D1938)` 23 words). Tip xvfb
2026-09-09 ~16:15 CT STOP **`pc=800d1938`** (`CPU_BOUNDARY` `ra=800d1928`
`a0=800ae6a8` `a1=800d19dc`) / `startup=PARTIAL` / `EXIT:2`.
The summary records the proven CPU refusal as **`menu=NOT_REACHED`** and keeps
the pending human look as a separate **`visual_check=REQUIRED`** marker;
`tools/native_boot_check.py` requires both, so a presented frame cannot be
mistaken for a reached menu. Folded SC02 PAC0 `8014E934…80150EC4` (60 leaves /
2404 words from `8e857c7f0`) onto tip with D18 retained. The SC02 hole
`80150EC4…80153C8C` is closed: its 13 differing spans are recovered, each a
single data reference shifted by the member's `+0x888` block offset, and all
re-earned MATCH against the SC02 blob. Remaining SC02 work is 272 known spans
— now 16 known spans (1,416 bytes) where the two members hold different code
rather than a retargeted data reference: `8013C9C4`, `8013D330`, `80164E40`,
`8017BEBC`, `8017BEE4`, `8017BF70`, `8017BFF8`, `8017C080`, `8017C0DC`,
`8017C120`, `8017C24C`, `8017DF18`, `8017E22C`, `8017E254`, `8017E298`,
`8017E324`. For example `8017BFF8` returns `D_801857E8` in member 0012 while
SC02_031 holds an unrelated store/`lwc2` sequence there, so these need their own
SC02 decompilation rather than an adaptation; seven of them have Druthulu
`shared/ov` donor shapes that still need their extern declarations. Next MAIN10
hole `800D1938+`.
Scanout enabled.

## SC02 word-lane provenance (2026-09-10)

The SC02 word lane's authority is **the image the guest itself loads**, not
`artifacts/bfm-takeover-20260907/sc01-title-code.bin`. That capture is a
different member: its overlay words match SC01.CD/extracted `sc01` data and
diverge from the resident image at the first data reference (word 48 of
`func_80128288`, `3C02801A` vs the resident `3C02801B`).

`MUSASHI_DUMP_RAM=<path>` captures the guest's 2 MiB main RAM at the boundary
stop, so the resident overlay can be compared directly. Run with the disc
arguments and auto-start to reach it:

```sh
SDL_VIDEODRIVER=x11 MUSASHI_BOOT_AUTO_START=1 MUSASHI_HOLD_WINDOW_MS=1000 \
MUSASHI_DUMP_RAM=/tmp/ram.bin \
xvfb-run -a build/musashi_native_boot extracted/disc/files/SLUS_007.26 \
  extracted/disc/disc.cue extracted/disc/disc.bin
```

Measured against that resident image (2026-09-10, stop `pc=801282ac`):

| streams | vs resident image |
| --- | --- |
| 1613 pre-existing (leaves folded before the batch work) | all match |
| 284 added by the member-0012 retargeting batches | all mismatch |

The port's `OVERLAY_WORD_MISMATCH` guard is why the run refuses there: it
compares each carved word with guest RAM and fails closed on a difference, so
no wrong word can execute. `src/overlays/sc02_0031/80128288.c` has been
re-derived from the resident image (dispatch table `D_80184F08`, oracle MATCH
17/17) as the first repair. All 283 remaining batch streams have since been
re-derived the same way (279 by automatic retargeting, 4 by hand: the
jump-table base `0x801B5BA8` for `func_80154C24` and the data blocks for
`func_8013C9C4`/`func_8013D330`/`func_80164E40`), each re-earning MATCH against
the resident image. **All 1907 wired SC02 streams now equal the resident
image** and the guard has no mismatch to report.

The walk then continues: `func_801612B8` (21/21) and `func_80133784`
(203/203, donor register pins retargeted to this member's boxes and counters)
were carved from the resident image as the next leaves, and the run now clears
the SC02 path entirely. It stops at `pc=80047d3c` in the main executable on an
unsupported GTE move (`mtc2 $a0, $30`) called from `func_80133784`, which is a
device-layer gap rather than a carve gap — the next port task.
No decomp claim is withdrawn for MAIN member 0012 — those registry entries were
verified against member 0012 and remain valid there; only their SC02_031
retargeting was built from the wrong image.


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

Mounted native startup now completes the full sound initializer and returns
naturally to `800101FC`, then enters file loading at `8001971C`. All fourteen
remaining sound/TOC streams (575 words) are mapped and byte-checked against the
pinned EXE. Actual GetTN/GetTD commands read all four mounted disc tracks; source
code writes the complete track table and restores its caller stack. Xenogears'
MIT PsyCross ADSR helper supplies configurable envelopes in the shared SPU owner.
Actual mode4 reverb feedback RAM writes are observed at the final sound return.

The sound checkpoint passes707 pytest tests plus84 subtests,21 graphics and10
headless CTests. Its final trace checker passes108 focused tests, including
malformed logs, packet/order/deadline mutations and missing real reverb work.
See `artifacts/spu-startup-20260906/outer-verification.json`. The retained binary
below belongs to that checkpoint; the working build continues beyond it.

```sh
python3 tools/native_spu_boot_check.py --sound-outer \
    artifacts/spu-startup-20260906/native/sound-outer-native-boot \
    extracted/disc/files/SLUS_007.26 extracted/disc/disc.cue extracted/disc/disc.bin
```

The retained sound checkpoint is historical; the current draw continuation
stops at BIOS/GTE initialization `80053CF8` after DMA2 and display setup. Progressive VSync remains conditional on actual source/GPU
state, while the interlaced `XOR` path is unsupported. Hardware timing/DSP
rounding, audible game sound and the menu remain unproven.

**Menu: NOT_REACHED.** The four-input check below opens the pinned disc and real
SDL audio owner; the one-EXE diagnostic intentionally retains its unmounted
`80044DBC` boundary.

In the preceding CD phase, the game issues `01`, `0A`, `0C`, drains four source
CD interrupts, and publishes
main gains `7FFE`, CD gains `3FFF`, and control `C001`. CD, SPU, Timer1, Timer2,
SIO and real VBlank events share the existing device epoch; reads do not create
time. Full digital input callbacks now return through their source, with
256-byte BIOS scratch `[84D8,85D8)`, eight return records and a counted
16384-instruction limit. The cold fixture covers three rejected `43` attempts
and recovery; native polling is timing-dependent and is not that fixture trace.

Validation: 633 pytest tests plus 84 subtests, 21 graphics CTests, 10 headless
CTests and symbol checks pass. The final SPU checker additionally passes 32
focused tests after its hardening; the historical CD checkpoint retains its own
580-test evidence. Four new
compiled digital-IRQ mutants and a live SDL no-queue mutant are rejected.
Real PipeWire queue/drain proves output progress; audible game sound, complete
BIOS/hardware cycle parity, the menu and launcher acceptance remain unproven.
The shared SPU now performs two actual 16-byte uploads, clocks all 24 voices,
registers DMA callback `3AA18` once, and opens/enables one polling event. Final
main gains are `7FFE`, CD gains are zero, and control is `C000`; sound RAM at
`1000..100F` contains the source-uploaded `07` bytes. The bounded synthesis subset
supports filter 0 and active ADSR `0000/0000`, with explicit refusals outside it.
Manual writes commit actual RAM synchronously under the documented native
policy; physical FIFO/key subphase and measured Gaussian rounding remain unproven.
The next common-attribute call also returns naturally at `8002C974`: seven actual
register writes restore CD gains `3FFF` and control `C001`, retaining the event
and uploaded RAM. Its live checker and 47 focused tests pass; evidence is sealed
in `artifacts/spu-startup-20260906/common-verification.json`. Reverb processing
and CD track-table commands remain ahead in the outer sound initializer.

Historical common-attribute checkpoint command (requires its earlier binary):
```sh
python3 tools/native_spu_boot_check.py --common-attributes \
    build/menu-resume/musashi_native_boot extracted/disc/files/SLUS_007.26 \
    extracted/disc/disc.cue extracted/disc/disc.bin
```

See [menu continuation](MENU-BOOT-CONTINUATION.md) and
`artifacts/cd-native-owner-20260906/` for source authority, logs and reviews.

The native targets are **diagnostics and an asset viewer**, not a bootable game.
Matched fixed-point functions are linked, but `pc_port/main.c` does not execute
the retail startup loop. Native startup executes through CD initialization; later game startup and
scene dependencies remain incomplete.

The earlier Checkpoint P viewer pause (2026-09-03) is historical. The current
priority is genuine native menu boot: see `tasks/plan.md` and the freshly
byte-checked [entry contract](NATIVE-BOOT-ENTRY.md). The viewer/GTE checks do
not establish native boot, a visible retail menu, or launcher acceptance.

What runs, all from the repository root after `./tools/run_tests.sh`:

```sh
# link check, pure fixed-point maths, no display needed
build/musashi_pc_smoke

# pinned EXE entry-data setup only; explicit synthetic return address, no game boot
build/musashi_boot_data_probe extracted/disc/files/SLUS_007.26

# one quad, verified by reading the framebuffer back
xvfb-run -a build/musashi_render_quad --screenshot quad.bmp

# any TMD model from the disc, auto-fitted, spun for N frames
xvfb-run -a build/musashi_render_tmd extracted/models/sc01_a97000.tmd \
    --frames 12 --screenshot model.bmp
```

Drop `xvfb-run -a` to see the window on a desktop. To find more models:

```sh
python3 tools/extract_cd.py  extracted/disc/files/SC01.CD --output extracted/sc01
python3 tools/extract_pac.py extracted/disc/files/SC01.CD --output extracted/pac/sc01
python3 tools/find_tmd.py    extracted/pac/sc01/0037_000.bin
python3 tools/extract_tmd.py extracted/pac/sc01/0037_000.bin --offset 0x87F0 \
    --output extracted/models/some_model.tmd
```

What does not run:

- **Integrated game execution.** The native executable does not run the game
  main loop or its input, audio, and scene paths.
- **Textured or per-vertex-coloured models.** The viewer and `tools/tmd.py`
  refuse them rather than draw garbage. Viewer expansion is not the current
  menu-boot milestone.
- **Lighting.** Every polygon takes its authored colour, flat.
- **Windows.** The roadmap names a Windows port. It is unverified: no MinGW
  cross-compiler is installed on the development machine, so nothing here
  has ever been built for it. Do not read "Linux and Windows" elsewhere in the
  docs as a claim that the Windows path works.

The smoke target verifies the link with pure fixed-point maths, so it runs
headless — requiring a window, display and GPU would make the build check
unusable in CI:

```text
musashi_pc_smoke: psyq rcos(0)=4096 rsin(0)=0 rcos(1/4)=0 rsin(1/4)=4096
```

Those values were read off the built library rather than assumed. PS1 fixed
point uses 4096 for 1.0 and 4096 units for a full turn, so cosine falls to zero
exactly where sine reaches one.

## Building

Native builds also require OpenSSL development headers and `libcrypto` for
the entry-data loader's pinned-image check. CMake uses `OpenSSL::Crypto`;
no TLS component is linked. When using Homebrew graphics dependencies, pass
`-DOPENSSL_ROOT_DIR=/home/linuxbrew/.linuxbrew` in a fresh build directory to
keep the dependency prefix consistent. Existing cached `OPENSSL_INCLUDE_DIR`
and `OPENSSL_CRYPTO_LIBRARY` selections must also point to that installation.

```sh
brew install sdl2 openal-soft     # or the system equivalents
./tools/fetch_toolchains.sh       # vendors PsyCross among the rest
./tools/run_tests.sh
```

`run_tests.sh` adds Homebrew to `CMAKE_PREFIX_PATH` when present; override with
`MUSASHI_CMAKE_PREFIX`. Configure with `-DMUSASHI_WITH_PSYCROSS=OFF` to build
the port without SDL2 or OpenAL at all — that path is verified and keeps the
decomp tooling usable on a machine with no graphics stack.

## What PsyCross actually provides

Measured from the built archive, not from its README: **399** C-linkage
functions, including `ResetGraph`, `DrawOTag`, `ClearOTagR`, `PutDrawEnv`,
`VSync`, `InitGeom`, `RotMatrix` and `RotTransPers`, plus 51 SPU, 20 CD and 19
pad entry points.

**There is no `libgs`.** Zero `Gs*` symbols are exported. This confirms
empirically what was previously only a research claim, and it matters: Brave
Fencer Musashi is a 3D game and will need TMD rendering. No permissively
licensed `libgs` exists anywhere. The options are to build on the
ordering-table level `libgpu` primitives that PsyCross does provide, to treat
the GPL-3.0 implementation in the Silent Hill decomp as a specification to study
rather than copy, or to accept GPL-3.0 for the port. **That is a licensing
decision, not a technical one, and it should be made before any TMD code is
written.**

## Upstream defects worked around

The build owns its integration rather than using PsyCross's own
`CMakeLists.txt`, which is only a source glob and two `find_package` calls. Four
problems had to be handled, all invisible to upstream because it is built with
MSVC and premake:

1. **The Psy-Q layer is nearly lost to a case-sensitive glob.** `src/psx` holds
   the implementations — `LIBGPU.C`, `LIBGTE.C`, `LIBCD.C` and eight more — in
   files named with an uppercase `.C`. A `*.c` glob silently skips all eleven on
   Linux, and the library still *builds and links*; it simply exports none of the
   Psy-Q API. Upstream's own `CMakeLists.txt` has this bug. A configure-time
   check now fails loudly if `LIBGPU.C` is not picked up, because the failure
   mode is silent and the symptom appears much later.
2. **GCC treats `.C` as C++.** The language is forced back to C so these symbols
   stay unmangled and callable from the decomp's C.
3. **`find_package(OPENAL)` in upper case** only resolves on case-insensitive
   filesystems, and upstream links a bare `OpenAL` target that modern config
   packages do not export. Handled by finding and linking the real targets.
4. **`include/psx/strings.h` shadows glibc's.** It is a Psy-Q compatibility stub
   pulling in `string.h` and `ctype.h`, and being on the `-I` path it wins over
   the system header, so `strcasecmp` is never declared on Linux even though
   `PsyX_main.cpp` includes `<strings.h>`. `pc_port/compat/psycross_compat.h`
   declares the prototype directly and is force-included into PsyCross sources
   only.

## Known hazard: 64-bit pointer truncation

`LIBETC.C` returns a callback pointer as an `int`:

```c
int old = (int)vsync_callback;
```

Harmless on the 32-bit PS1, lossy on x86-64. GCC 14+ makes it an error, which is
downgraded so the build completes, **but the truncation is real**: the handle
returned by `ResetCallback` and `VSyncCallback` must not be cast back to a
pointer on a 64-bit host. Anything relying on those return values needs fixing
before it can be trusted.

The VBlank scheduler is the only reviewed registration exception: it calls
`VSyncCallback` to install or remove its single callback, discards the returned
value, refuses to replace an existing callback, and never restores one. The
archive checker still rejects both APIs by default; its
`--allow-vsync-discard` switch is required explicitly by the native test
runner and leaves `ResetCallback` forbidden. That exception proves only that
the unsafe return is ignored, not that a host VBlank or game boot occurred.

`pc_port/irq_controller.c` supplies the native `I_STAT`/`I_MASK` storage used
by the display-backed scheduler probes. VBlank raises bit zero, the recovered
dispatcher acknowledges it with the retail mask write, and unknown addresses
are refused. This removes test-local IRQ register semantics; cold-start
ownership and general guest callback execution are still unfinished.

The native cleanup boundary is split across `pc_port/bios_events.c` and
`pc_port/bios_kernel.c`. They own a 22-record event pool and priority registry,
create the CD session through five class `F0000003` polling events plus IO/DMA
nodes, and remove only those owned resources at A0:72. The run closes five
handles, unlinks two nodes, preserves game RAM, and leaves
`bios_event_used=0` and `bios_cd_installed=0`. The actual CD handler is still
unsupported and refuses closed-loop execution if reached.

SYS(2) enables guest IRQ eligibility after cleanup. `pc_port/irq_scheduler.c`
keeps PsyCross's worker as a VBlank queue producer.
The owner pump consumes and coalesces pending edges at live FormatterCpu
instruction/call checkpoints, then runs the recovered dispatcher and consumes
the B0:17 continuation. The worker does not write guest RAM or hold a broad
host mutex across guest execution. The earlier cleanup gate reported guest IRQ
enabled with zero cold-prefix deliveries; the current StartCARD check reports
guest IRQ enabled with no fault. A separate live fixture covers scheduler
delivery. Production HBlank input and GPU_cw remain open. The optional serial
integration uses a dedicated 112-byte BIOS scratch frame `[8568,85D8)`, executes
five exact SIO configuration writes around a paced Timer2 sample before refusing
`F830` at `8005DB04` when only 16-bit providers are supplied. The current
byte-enabled metadata fixture instead reaches `8005DC04 -> 8005EAE8`;
`read16` does not advance Timer2. It is not a
natural controller transaction. The source ledger accounts for startup/input
instructions while Timer2 and bound SIO advance from actual host-time cuts;
CD and video deadlines remain disconnected. The source ledger reaches `950315`;
the earlier source-only Timer2 count `8039` is historical. Current Timer2 counts
vary with elapsed host time; retail phase parity is unproven. See
`artifacts/cd-init-device-20260905/contract.md` for the
source-authoritative three-boot CD contract.

The current native SIO owner is bound to digital port 1 and an SDL keyboard
provider on the same paced epoch. Startup reports `keyboard_polls=0` and no
DATA-pad packet, so provider binding is not natural input proof. Six metadata
edges are mapped, four new metadata arrays are integrated, and the legacy
16-bit path remains refused at `8005DB04`. The selected-device identity fix
and focused probe pass; the synthetic fixture reaches `DC04`/`EAE8` refusal
with metadata stores. See
`artifacts/controller-protocol-20260905/integration-contract.md` for the
bounded retail and native contract.

The graphics gate reports `GPUREAD=00000400` and query-7 leaves `GPUREAD=400`;
the physical GPU revision response is unproven. Blank-only presentation is
available while geometry, VRAM transfer, enabled scanout, and production HBlank
input remain unsupported. The latest validation is **557 passed plus 84
subtests** and **21/21 CTest tests**, with graphics/headless builds, archive
symbol verification, focused NTSC/live checks, and diff checks passing. The
Timer2 owner is integrated under a paced host-time device epoch with variable
phase; six additional Timer2 focused tests pass, including the large-
`UINT64_MAX` case. The native final check still stops at the CD byte boundary.
The independent source check covers 26 newer exports and 1,528 exact words;
24 of these exports remain source-only, with two used by the metadata stage. This source proof is separate
from native mapped/runtime proof.
Source exports include **121/66**
word-exact event-registration/helper exports and eight five-word callback exports; **40/28/37** remains
historical.

The native continuation CPU comparison covers all 32 GPRs plus HI/LO at five
interim boundaries. The historical StartCARD comparison reports 13/15/14 GPR differences at
ENTRY/RETURN/NEXT; the selected frame agrees except RETURN `a0` (native `1`,
retail `2`, following the SYS2 source value). Full CPU parity is unestablished;
the native initial GPR/HI/LO profile and incoming RA are zeroed, not
retail-seeded.

The cleanup validation is deliberately scoped to owned state: five CD records
(140 bytes) and all 22 status words match before and after cleanup. The full
616-byte initial table does not match because retail unused slots retain prior
BIOS payloads and stale stack words; native startup does not seed those values.
Separate allocation serials/leases detect replacement of owned slots while
preserving guest handles and the B0 low-16-bit alias. The full-table comparison
in `tests/test_bios_events.py` remains a same-input cleanup test; the kernel
test's negative control records why it is not initial-RAM parity.

The preceding event milestone prepared native input C0 kernel ownership. The eight
event records match retail's first five words and the registration `v0=1` is a
source comparison literal for a void path, not successful API proof. BU state
matches; CPU comparison has 15/12 GPR differences and HI/LO differences while
selected `v0/gp/sp/fp/ra` match. The eight callback flag stores pass focused executor tests; their delivery
was not observed during this short boot window. Menu, hardware, full BIOS cold-boot, cycle, low-RAM,
and whole-CPU parity remain unproven.

## Rendering: one quad, verified headless

P1 draws a red `POLY_F4` on a blue field through the Psy-Q layer and verifies
it in CI with no display. `tools/render_check.py` runs `musashi_render_quad`
under `xvfb-run` with Mesa's llvmpipe, reads the pixels it reports, and judges
them with `tools/vram_pixel.py`. Sampled: inside `rgb5=(30,0,0)`, outside
`rgb5=(0,0,31)`. Without `xvfb-run` the ctest is reported as **skipped**, never
as passed.

`--screenshot PATH` writes the frame as a BMP for looking at with human eyes.
It is off by default, so the automated check stays a pixel comparison rather
than something that quietly depends on file output.

Verified on real hardware as well as software: on Mesa Intel (ARL) the sampled
values are identical to llvmpipe's, so the CI result is not an artefact of the
software renderer.

Getting a single quad on screen took a long chain of measurements, and several
of my own intermediate conclusions were wrong. They are corrected here because
the wrong ones were plausible.

### Root cause: two consumer-side defines

**`USE_EXTENDED_PRIM_POINTERS` must be defined by the consumer.** The
primitive-tag macros (`setaddr`, `getaddr`, `nextPrim`, `isendprim`) are gated
on it — *not* on the 64-bit check that sizes the tag struct. Without it, on
x86-64, a 12-byte tag holding a `uintptr_t` is filled by macros that truncate
every pointer to 32 bits and test for a 24-bit terminator. PsyCross never
defines it; upstream sets it in premake. It is now PUBLIC on `psycross_static`
because the macros expand in our code too.

**`USE_PGXP` defaults to that same value, and must be held off for now.** With
PGXP on, `VERTTYPE` is a 16-bit `half` float under C++ and a `short` in C.
Same byte layout, different type: the shorts our C writes are reinterpreted as
float16 denormals, so `80` becomes ~5e-6 and every vertex normalises to
exactly `-0.5` — two degenerate triangles that rasterise nothing, with no error
anywhere. PsyCross's `_HF()` macro exists precisely to convert in C mode. PGXP
stays off until the port has real GTE transforms to feed it.

### Verification must read framebuffer 0, not VRAM

`GR_ReadVRAM` can never observe a rendered frame. Its backing array is uploaded
*to* the GPU as texture source; both places that copy GL output toward it pass
`update_vram=0`. And `GR_SaveVRAM`'s `bReadFromFrameBuffer` argument is unused —
it dumps that same array. An earlier note here called an all-black `GR_SaveVRAM`
capture "decisive" evidence that rendering failed. It was not evidence of
anything; it only showed the CPU array was empty, which it always is.

The render target therefore reads framebuffer 0 with `glReadPixels`, fetched
through `SDL_GL_GetProcAddress`, after `DrawSync` and before `PsyX_EndScene`
presents the frame, and packs the 8-bit sample the way VRAM stores it so the
harness judges one format.

### A measurement trap

`DrawOTag` calls `DrawAllSplits` internally, which ends in `ClearSplits()`.
Reading `g_splitIndex` after `DrawOTag` therefore always shows zero, and an
earlier note here concluded from that reading that the ordering-table walk was
broken — a second, separate fault. It was never broken. Measured correctly, by
calling `ParsePrimitivesLinkedList` directly before anything draws, the walk
produces one split and six vertices, identical to the single-primitive path.
There was one fault, not two.

### Colours round-trip lossily

8-bit colour becomes 5-bit VRAM and comes back through GL: red `248` sampled
as `241`. The judge asks for the expected channel to dominate and the others to
stay near zero, in 5-bit units, rather than for an exact value.

## A real model renders, without libgs

`musashi_render_tmd` loads a model extracted from `SC01.CD`, transforms it
through the GTE and draws it as ordinary `libgpu` primitives. ctest verifies it
headlessly alongside the quad. The target at `0xA97000` is a hexagonal column,
18 primitives, drawn in its authored beige `(240,197,152)`; sampled inside as
rgb5 `(29,24,18)` against an expected `(30,24,19)`.

This is the `libgs`-free path the project chose. No permissively licensed
`libgs` exists, so the model is walked here and emitted as `POLY_G3` and
`POLY_G4` into an ordering table, which is what `libgs` would have done
internally.

**Lighting is not set up.** Every vertex takes its primitive's own colour, so
the model draws flat rather than shaded. That is enough to prove geometry
reaches the screen, which is what this target exists for.

**`tools/tmd.py` is the tested reference for the format**, and refuses the
variants it does not read. The C reader in the port covers the same subset and
refuses the same cases, rather than drawing garbage from a packet shape it does
not understand.

### The 64-bit width hazard, a third time

`RotTransPers` takes an `int*` for the packed screen coordinate, not a `long*`.
Using a `long` on x86-64 writes eight bytes where four are expected and
corrupts the neighbouring entry. This is the same class of bug as the ordering
table being `OT_TAG[]` rather than `u_long[]`. Screen coordinates are now
unpacked explicitly into `setXY3`/`setXY4` instead of being punned through a
pointer.

### Judging arbitrary colours

The pixel judge originally asked for one dominant channel and near-zero others.
That suits a red quad on blue and is wrong for anything else: this model's
beige has three substantial channels, and the judge rejected a correct frame.
It is now a per-channel tolerance of 3 in 5-bit units, which covers both the
primaries and authored colours without special-casing either.

### Ordering tables must not be declared `u_long`

Found while getting this far, and it applies to all ported code.

PS1 source declares an ordering table as `u_long ot[N]`, because a tag was
exactly one 32-bit word. On x86-64 an `OT_TAG` is **12 bytes**: `DECLARE_P_ADDR`
carries a `uintptr_t` plus bitfields, and `P_LEN` becomes 3. `u_long` is 8.

So `u_long ot[8]` hands `ClearOTagR` a 64-byte buffer for 96 bytes of writes.
It corrupts memory and crashes. Every ordering table in ported code must be
declared `OT_TAG[]`, casting at the `ClearOTagR` and `DrawOTag` call sites,
which take `u_long *`. This is the "structs containing pointers change size on
64-bit" hazard in its most concrete form.

### Ordering table direction

`ClearOTagR` chains `ot[i]` to `ot[i-1]`, making `ot[0]` the terminator and
`ot[n-1]` the head. Drawing with `DrawOTag(ot)` walks nothing and fails
silently.

### Two inconsistent VRAM packings in PsyCross

The framebuffer path packs a pixel as `r | (g << 5) | (b << 10) | (a << 15)`
with 5-bit components, which is the PS1 format and what `tools/vram_pixel.py`
implements. `GR_ClearVRAM` instead writes `r | (g << 5) | (b << 11)` with
*unmasked 8-bit* components, so clearing to red 255 yields `0x00FF` rather than
`0x001F`. Read-back of rendered content follows the first; do not calibrate
against `GR_ClearVRAM`.

## Vendor matched intake (cleaned)

Raw Druthulu matched sources live under `vendor/bfm-decomp/` (see `VENDOR.md`).
The PC port does **not** compile those giant TUs directly.

Smoke-matched symbols (`func_80012AB0`, `func_80012E6C`, `func_8001311C`,
`func_80013154`) link from cleaned house-style files:

- `src/main/80012ab0.c`
- `src/main/80012e6c.c`
- `src/main/8001311c.c`
- `src/main/80013154.c`

Local cleaned forms win over vendor `__asm__("$0")` / dump style. Cleanup rules:
`docs/VENDOR-CLEANUP.md`.

```sh
# default: cleaned src/main leaves (same as before)
cmake -S . -B build
cmake --build build --target musashi_pc_smoke

# vendor-aware configure: asserts vendor/bfm-decomp exists; still links cleaned leaves
cmake -S . -B build -DMUSASHI_USE_VENDOR_BFM=ON
cmake --build build --target musashi_pc_smoke
ctest --test-dir build -R musashi_pc_smoke --output-on-failure
```

`musashi_native_boot` remains on the address-file / word-array interpreter path for
most of the EXE; only the smoke-matched leaves above are compiled as host C today.
Widening intake means cleaning more vendor functions into `src/main/800*.c` and
adding them to CMake — not flipping on all of `vendor/bfm-decomp/src/`.
