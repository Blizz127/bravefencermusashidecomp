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

## Rendering: blocked, and what is established

P1 set out to draw one quad and assert its pixels headlessly. **It does not
render.** The work below is real and the failure is precisely located, but no
pixel has been produced.

What is established:

- **PsyCross initialises headlessly.** Under `xvfb-run` with
  `LIBGL_ALWAYS_SOFTWARE=1` it reports llvmpipe and an OpenGL 4.6 core context,
  and `PsyX_Initialise`/`ResetGraph`/`PsyX_Shutdown` complete cleanly.
- **VRAM read-back works.** Writing a colour with `GR_ClearVRAM` and reading it
  through `GR_ReadVRAM` round-trips, so the sampling half of the check is sound.
- **Nothing reaches the framebuffer.** After `ClearOTagR`, `addPrim`, `DrawOTag`
  and `DrawSync` — with and without `PsyX_BeginScene`/`PsyX_EndScene`, and with
  `GR_StoreFrameBuffer` plus `GR_ReadFramebufferDataToVRAM` — every sampled
  pixel is zero. PsyCross's own `GR_SaveVRAM(..., bReadFromFrameBuffer=1)`
  writes a 1MB TGA in which all 524,288 pixels are zero. The render, not the
  read-back, is what is failing.

Untested next steps: whether an offscreen GL context under llvmpipe ever
populates the path PsyCross reads from, whether a window swap is required
before the framebuffer is valid, and whether a real display changes the result.

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
