# Brave Fencer Musashi decompilation

This repository is the source-faithful starting point for a byte-for-byte
decompilation of the North American PlayStation release of *Brave Fencer
Musashi*. The decompilation is the authority for the eventual Linux and
Windows ports; a native port must not become a replacement implementation.

The retail CHD is intentionally not stored here. Each contributor supplies a
lawfully obtained copy and registers it with `tools/register_retail.py`. The
registration record stores only the expected media identity (size and SHA-256)
and extraction status. Until the disc is extracted and the `SYSTEM.CNF` boot
path and `PS-X EXE` are observed, executable metadata remains unresolved.

## Current state

The retail disc has been registered, extracted, and its boot executable
observed. `SLUS_007.26` is pinned by hash, and splat produces a first
disassembly covering 99.50% of the image across 1334 functions.

Nothing is matched yet, and the original compiler is still unidentified. See
[docs/MILESTONE-1.md](docs/MILESTONE-1.md) for the observed evidence,
[docs/ROADMAP.md](docs/ROADMAP.md) for the staged workflow, and
[docs/COMPILER-ID.md](docs/COMPILER-ID.md) for the compiler-identification
contract.

## Provenance workflow

```text
register CHD -> verify hash -> extract/mount -> discover SYSTEM.CNF/PS-X EXE
            -> record executable identity -> pin toolchain -> match bytes
```

Use the scripts from the repository root. They fail closed on missing tools,
hash mismatches, malformed `SYSTEM.CNF`, and non-PS-X executables.

Extraction uses MAME `chdman extractcd` to create a local BIN/CUE pair, then
`dumpsxiso` to read the filesystem consumed by the identity tool. A generic
ISO9660 reader must not be substituted here: it sees only the 2048-byte Form1
sector area and silently truncates every CD-XA Mode2/Form2 file on the disc.
See [docs/MILESTONE-1.md](docs/MILESTONE-1.md) for the measurements. All
extraction outputs live below the ignored `extracted/` directory.

`dumpsxiso` is built locally from the pinned mkpsxiso checkout under
`tools/third_party/` (gitignored):

```sh
git clone --recurse-submodules https://github.com/Lameguy64/mkpsxiso.git tools/third_party/mkpsxiso
cmake -S tools/third_party/mkpsxiso -B tools/third_party/mkpsxiso/build -DCMAKE_BUILD_TYPE=Release
cmake --build tools/third_party/mkpsxiso/build -j"$(nproc)"
```

No copyrighted game code, executable, textures, audio, or disc image belongs
in this repository. See [LICENSE-NOTES.md](LICENSE-NOTES.md).
