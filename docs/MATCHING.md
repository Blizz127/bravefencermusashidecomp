# Matching log and method

## Status

One function is byte-verified against retail. The original compiler is still
**unresolved**, and the first match did nothing to change that — see the
non-discrimination result below, which is the more important finding.

| vram | words | source | verdict |
| --- | --- | --- | --- |
| `0x80012AB0` | 3/3 | `src/main/80012ab0.c` | MATCH |

Reproduce with:

```sh
python3 tools/build_candidate.py src/main/80012ab0.c \
  --symbol func_80012AB0 \
  --toolchain gcc-2.7.2-psx \
  --toolchain-root "$PSYQ_TOOLCHAIN_ROOT" \
  --maspsx "$PSYQ_TOOLCHAIN_ROOT/maspsx/maspsx.py" \
  --output /tmp/candidate.bin
python3 tools/match_function.py --vram 0x80012AB0 --size 0xC --candidate /tmp/candidate.bin
```

## A match is not a compiler identification

The first matched function was compiled against every locally available
toolchain at three optimization levels and two `-G` values. **All 18
configurations produced byte-identical output:**

| toolchain | `-O1` | `-O2` | `-O3` |
| --- | --- | --- | --- |
| `gcc-2.6.0-psx` | MATCH | MATCH | MATCH |
| `gcc-2.7.2-psx` | MATCH | MATCH | MATCH |
| `gcc-2.7.2-cdk-psx` | MATCH | MATCH | MATCH |

(`-G0` and `-G8` agree throughout.)

A three-instruction arithmetic leaf has exactly one sensible encoding, so its
codegen is invariant across compiler versions and optimization levels. It
proves the build and comparison pipeline works. It is worth **zero** evidence
about which toolchain built the game.

The practical consequence: **discriminating functions must be selected
deliberately, not stumbled into.** A function only carries version evidence if
candidate toolchains actually disagree on it. Before treating any future match
as toolchain evidence, compile it against the full candidate set and confirm
the alternatives *fail*. A match that every candidate reproduces is a pipeline
test, not a fingerprint.

Properties that make a function likely to discriminate:

- enough live values to force register allocation choices
- a non-trivial return path, so return-delay-slot behaviour is exercised
- division or modulo, whose expansion varies by ASPSX version
- `-G`-sensitive access to small globals, which changes `$gp` addressing
- floating point, which becomes libgcc calls under `-msoft-float`

## Division-idiom probe: one flag established, version still open

`tools/idiom_probe.py` reads the division expansion retail uses, emits the same
construct with each candidate toolchain, and compares mnemonic shape with
operands ignored.

Retail is unambiguous. All **69** division sites use the same expansion:

```text
div|divu  ->  bnez  nop  break        (100% of sites)
```

That is the divide-by-zero guard. Probing the candidates isolates one build
setting cleanly:

| maspsx division expansion | candidate expansion | verdict |
| --- | --- | --- |
| off (`idiom_probe --no-expand-div`) | `div + mflo jr nop` | differs from retail |
| on (default) | `div + bnez nop break` | reproduces retail |

**Established: the build requires maspsx division expansion.** Without it no
candidate emits the guard at all, so this is a configuration fact read off
retail bytes rather than a preference. `build_candidate.maspsx_command`
therefore passes `--expand-div` by default, and `idiom_probe` keeps
`--no-expand-div` only to reproduce the contrast above.

**Not established: the compiler version.** With `--expand-div` enabled, all
three locally installed toolchains reproduce the expansion identically:

| toolchain | ASPSX | expansion |
| --- | --- | --- |
| `gcc-2.6.0-psx` | 2.34 | reproduces |
| `gcc-2.7.2-psx` | 2.56 | reproduces |
| `gcc-2.7.2-cdk-psx` | 2.67 | reproduces |

ASPSX 2.34, 2.56, and 2.67 emit the same guard shape, so the idiom separates
"guard" from "no guard" but not one ASPSX version from another. `gcc-2.8.0-psx`
(ASPSX 2.77) and `gcc-2.8.1-psx` (2.79) are **not installed locally** and
remain untested; they are the versions most likely to differ, since the 1999
Square titles moved to them. Obtaining them is the next concrete step for this
probe.

A sharper variant worth building: compare the *full* expansion window rather
than a three-mnemonic prefix, including where the guard places `mflo`/`mfhi`
relative to the branch, and how a division by a constant is strength-reduced.
Constant division is the more promising discriminator, because magic-number
multiplication changed across GCC 2.x.

## Caveat on the return-delay-slot heuristic

Commit `915c6fe` recorded a 17.81% return-slot fill rate and cited the rule
that GCC 2.8.1 fills the slot after `jr $ra` while 2.7.2 does not. A trivial
leaf compiled here with `gcc-2.7.2-psx` **did** fill its return slot, and the
matched `0x80012AB0` has its `andi` scheduled into the delay slot in retail
too.

So the rule is not a flat property of the compiler. When the slot is trivially
fillable, 2.7.2 fills it. The heuristic only carries signal where scheduling is
genuinely constrained, which means the 17.81% aggregate cannot be read as
"mostly 2.7.2" without segregating functions by scheduling difficulty first.

## Operational note

`argparse` rejects an option value that looks like a flag, so the optimization
and `-G` arguments must use the `=` form:

```sh
--optimization=-O2 --gp=-G0      # correct
--optimization -O2               # error: expected one argument
```
