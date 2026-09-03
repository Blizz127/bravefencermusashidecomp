# Roadmap

The project is intentionally staged so that every later porting decision is
backed by an observed retail executable.

1. **Retail registration**
   Register the contributor's CHD and verify the pinned size and SHA-256.
2. **Disc extraction**
   Extract the CHD with an installed, explicitly selected `chdman` build (or
   another reviewed extractor). If no extractor is available, stop; do not
   infer files from the CHD container.
3. **Boot identity**
   Discover `SYSTEM.CNF`, resolve its `BOOT` target, locate the `PS-X EXE`,
   and record its header fields plus whole-file and header hashes.
4. **Toolchain identification**
   Determine the original compiler, version, assembler, linker, flags, and
   post-link transforms. See [COMPILER-ID.md](COMPILER-ID.md).
5. **Static layout and symbols**
   Partition the executable into code/data, establish sections and labels,
   and add only evidence-backed declarations under `asm/` and `src/`.
6. **Byte matching**
   Compile one bounded function at a time and compare the resulting bytes with
   the pinned executable. A successful build is not a match without a binary
   comparison.
7. **Runtime validation**
   Validate the matched executable under a deterministic PS1 emulator, then
   exercise the same decompilation-backed code through the Linux and Windows
   ports.

Steps 1 through 3 are complete and recorded in
[MILESTONE-1.md](MILESTONE-1.md). Step 5 has a first pass: splat covers 99.50%
of the executable as raw assembly. Step 4 has not started, and no work toward
step 6 or 7 has been attempted.

## Evidence tracks

- **Static matching:** rebuilt MIPS bytes equal the pinned retail bytes for a
  precisely named function, object, overlay, or executable range.
- **Emulator observation:** the rebuilt PS1 artifact is executed and observed
  in a pinned emulator. A static match alone does not establish this.
- **Native runtime:** Linux and Windows execute the same decomp-owned C through
  reviewed platform adapters. The current smoke target proves plumbing only.
- **Human parity:** a person completes a documented comparison against retail
  behavior. Automated tests and screenshots do not substitute for this gate.

## Extraction pipeline

The pipeline is `chdman extractcd` to produce a BIN/CUE pair, then `dumpsxiso`
to read the filesystem:

```text
chdman extractcd -i <verified.chd> -o <ignored/disc.cue> -ob <ignored/disc.bin>
dumpsxiso -x <ignored/files> -s <ignored/layout.xml> <ignored/disc.cue>
```

`dumpsxiso` replaced an earlier `bchunk` + `7z` stage that silently truncated
every CD-XA Mode2/Form2 file on the disc. Any future substitution must be
measured against the sizes recorded in [MILESTONE-1.md](MILESTONE-1.md), not
assumed equivalent because it produces files without erroring.

## Milestone 2 precondition

Milestone 2 is compiler identification. It must not conclude from a plausible
version string or a build that merely succeeds. It requires disassembly or
linker fingerprint evidence drawn from the pinned executable, per
[COMPILER-ID.md](COMPILER-ID.md), and the first byte comparison of a rebuilt
function against retail.
