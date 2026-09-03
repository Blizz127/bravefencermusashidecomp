# Matching log and method

## Status

One function is byte-verified against retail. The compiler is still
**unresolved**, but no longer unconstrained: half the candidate set has been
eliminated by a complex function — see "First elimination" below. That result
is **unreplicated**; a second function was attempted and came out inconclusive.

| vram | words | source | verdict |
| --- | --- | --- | --- |
| `0x80012AB0` | 3/3 | `src/main/80012ab0.c` | MATCH |

Reproduce with:

After `./tools/fetch_toolchains.sh`, every path resolves from the repository:

```sh
python3 tools/build_candidate.py src/main/80012ab0.c \
  --symbol func_80012AB0 --toolchain gcc-2.7.2-psx --output /tmp/candidate.bin
python3 tools/match_function.py --vram 0x80012AB0 --size 0xC --candidate /tmp/candidate.bin
```

## First elimination: `func_80012E6C`

The approach that worked is the one the negative results pointed at: take a
real function with room for compilers to disagree, compile it against the whole
candidate set, and see who cannot produce it.

**Target.** `func_80012E6C`, vram `0x80012E6C`, `0x108` bytes (66 words). A
relocation-free leaf — no `jal`, no `%hi`/`%lo` — so its compiled `.text` is
final and needs no linking. 9 distinct registers with a mix of multiply,
divide, shift, load, compare and branch. Decompiled with m2c and cleaned into
`src/main/80012e6c.c`.

Selection note: branch count is a poor proxy for discrimination.
`func_8001923C` has 25 branches but only 4 distinct registers and no loads,
shifts or multiplies — a repetitive compare chain every compiler encodes
identically. Instruction *variety* and register count matter more.

**Result**, via `tools/discriminate.py` over `-O0..-O3` x `-G0/-G4/-G8`
(12 configurations per toolchain):

| toolchain | PSY-Q | best word count | verdict |
| --- | --- | --- | --- |
| `gcc-2.7.2-cdk-psx` | 4.1 | **66** | survives, 36.36% |
| `gcc-2.7.2-psx` | 4.0 | **66** | survives, 34.85% |
| `gcc-2.6.0-psx` | 3.5 | **66** | survives, 34.85% |
| `gcc-2.8.0-psx` | 4.3 | 67 | **eliminated** |
| `gcc-2.8.1-psx` | 4.4 | 67 | **eliminated** |
| `gcc-2.91.66-psx` | 4.5 | 63 | **eliminated** |

Retail is 66 words. Three candidates hit it exactly; three never reach it at
any tested setting. The 2.8.x pair bottom out at 67 words and 2.91.66 at 63.

**Candidate set: 6 -> 3.** The surviving set is PSY-Q 3.5, 4.0 and 4.1. This
corroborates the 1998 Square cluster around GCC 2.7.2 / PSY-Q 4.0 without
having assumed it: the registry deliberately included the later releases so a
2.7.2 answer could have been falsified, and they failed on their own.

### What this does and does not establish

**Instruction count is the load-bearing signal, not the ratio.** It is
structural: it asks only whether a compiler can reach the right shape from this
source, which survives an imperfect decompilation. The ratios (34-36%) show the
C is plainly not the original source yet.

**The three survivors are not separated.** Their spread is 1.52 points, well
inside the noise of an imperfect decompilation. Nothing here distinguishes
2.6.0 from 2.7.2 from 2.7.2-cdk.

**The elimination is conditional on the decompiled C being approximately
correct.** If the C is wrong in a way that systematically suits the older
backend, the result would be an artifact. Two things argue against that: the
count match is exact rather than close, and it holds across all 12 flag
configurations rather than at one lucky setting. It should still be re-checked
against a second complex function before being treated as settled.

Per `docs/COMPILER-ID.md` the compiler therefore remains **unresolved**. This
is recorded as candidates eliminated, not as an identification.

## Replication attempt: inconclusive

The elimination above rests on a single function, so it was re-tested against a
second one. **The replication did not succeed**, and the first result therefore
stands unreplicated.

**Target choice.** `func_80013028` was rejected despite being the documented
fallback: it has the same signature as `func_80012E6C` and the same +/-1 nudge
logic, so a decompilation wrong in the same way would confirm itself.
`func_80016714` was also rejected — it is a `memset`-style zero-fill with
alignment handling, and if it is linked Psy-Q library code rather than Square's
own it was built by Sony with different flags, which would contaminate the
result.

`func_80013154` was chosen instead: vram `0x80013154`, `0xAC` (43 words),
relocation-free, and structurally independent — a different signature
(`s32 f(s16, s16, s32)`), nested conditionals, and clearly game logic rather
than a library routine.

**Result.** No candidate reached 43 words from `src/main/80013154.c`:

| toolchain | best word count |
| --- | --- |
| `gcc-2.6.0-psx` | 44 / 41 |
| `gcc-2.7.2-psx` | 45 / 40 |
| `gcc-2.7.2-cdk-psx` | 38 |
| `gcc-2.8.0-psx` | 38 |
| `gcc-2.8.1-psx` | 38 |
| `gcc-2.91.66-psx` | 38 / 32 |

This says nothing about any compiler. It says the decompilation is not yet
close enough — the C is committed as work in progress rather than as evidence.

**A tool defect this exposed.** `discriminate.py` initially reported this as
"ELIMINATED (6)", which is badly wrong: eliminating every candidate is not a
discrimination result. Elimination is only meaningful relative to a candidate
that *did* reproduce the retail shape, so with no survivor the source is at
fault. The tool now reports `INCONCLUSIVE` and says so explicitly.

**Worth noting for the retry.** The word counts here spread from 32 to 45
across candidates, far wider than on `func_80012E6C`. Once the C is accurate
this function should discriminate *more* sharply, not less.

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

**Not established: the compiler version.** The full candidate set is now
installed locally by `tools/fetch_toolchains.sh`, spanning PSY-Q 3.5 to 4.5.
Every one of them reproduces the expansion identically:

| toolchain | PSY-Q | ASPSX | division guard | `a / 10` |
| --- | --- | --- | --- | --- |
| `gcc-2.6.0-psx` | 3.5 | 2.34 | reproduces | identical |
| `gcc-2.7.2-psx` | 4.0 | 2.56 | reproduces | identical |
| `gcc-2.7.2-cdk-psx` | 4.1 | 2.67 | reproduces | identical |
| `gcc-2.8.0-psx` | 4.3 | 2.77 | reproduces | identical |
| `gcc-2.8.1-psx` | 4.4 | 2.79 | reproduces | identical |
| `gcc-2.91.66-psx` | 4.5 | 2.81 | reproduces | identical |

Both idioms are **definitively non-discriminating** across the entire PSY-Q
range. This closes the line of investigation rather than leaving it open.

## Why synthetic idiom probes fail here

The two results have different causes and together they generalise:

- The divide-by-zero guard is an **assembler** macro. ASPSX expands it, so it
  cannot separate compiler versions no matter which one emitted the `div`. The
  probe was testing the wrong layer.
- Constant division *is* a compiler transform, but magic-number strength
  reduction for `a / 10` produces the same sequence from 2.6.0 through
  2.91.66. These releases share a backend for straightforward code.

The generalisation: **simple single-expression probes cannot discriminate these
compilers.** Anything with one obvious encoding will be emitted identically by
all of them, which is the same reason the first matched function proved
nothing.

Discrimination requires constructs where the compilers have room to disagree —
register allocation under pressure with many simultaneously live values,
instruction scheduling through non-trivial control flow, and delay-slot filling
where the choice is genuinely constrained. Those are properties of *real*
functions, not of synthetic one-liners.

**Revised approach: stop building synthetic probes.** Decompile a genuinely
complex function from the executable and compile it against all six
candidates. The toolchains that fail to reproduce it are eliminated. This is
what established PSX projects actually rely on, and the harness needed for it
already exists.

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
