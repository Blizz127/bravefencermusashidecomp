# PC port

The port links the decompilation against
[PsyCross](https://github.com/OpenDriver2/PsyCross) (MIT), which reimplements
the Psy-Q libraries for PC on SDL2, OpenAL and OpenGL. It is vendored at a
pinned commit by `tools/fetch_toolchains.sh` and its checkout is ignored.

## Status

Plumbing only. Decomp-owned C reaches the Psy-Q layer and gets correct results,
which is what phase C1 set out to prove. Nothing renders yet, and no game code
is wired in.

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
