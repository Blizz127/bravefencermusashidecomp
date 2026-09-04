# Matching log and method

## Status

25 functions are byte-verified against retail — but only 3 are substantive;
the other 22 are two-instruction stubs. See "Counting honestly" below.
The 6→3 elimination is **replicated** across two independent functions, one of
them a verified-correct source. The compiler is still
**unresolved**, but no longer unconstrained: half the candidate set has been
eliminated by a complex function — see "First elimination" below. That result
is **unreplicated**; a second function was attempted and came out inconclusive.

| vram | words | source | verdict |
| --- | --- | --- | --- |
| `0x80012AB0` | 3/3 | `src/main/80012ab0.c` | MATCH |
| `0x80014128` | 8/8 | `src/main/80014128.c` | MATCH (first with a `jal`) |
| `0x800CF3B0` | 22/22 | `src/overlays/main_0007/800cf3b0.c` | MATCH (first in an overlay) |
| `0x8012BF4C` | 2/2 | `src/overlays/main_0012/8012bf4c.c` | MATCH (first in member 0012) |

21 further stubs in member 0012 are recorded in `provenance/matches.json`
rather than listed here.

## Counting honestly

`tools/progress.py` reports functions rebuilt from C and verified equal to
retail. It never reports a diff percentage: a project counting `objdiff` match
rate can show 100% while the "C" is verbatim `__asm__` transcription, and one
PSX project publicly retracted exactly such a figure as "true but meaningless".

That guard is not sufficient on its own. Reaching 25 matches took 22
two-instruction stubs — empty functions, single stores, plain returns. They are
genuine matches, and they are not meaningful progress. The tool therefore splits
the total, so the headline number cannot flatter:

```text
MATCHED 25 functions, 308 bytes
  of which trivial (<= 8 bytes): 22    substantive: 3
```

308 bytes against roughly 800KB of code is the honest picture.

## A destructive automation bug, caught only by re-verification

Batch-matching wrote each candidate's source, then deleted it when the build or
comparison failed. `func_8012BF4C` already had a hand-written, committed,
verified source; the batch overwrote it with m2c output, failed, and deleted the
file — destroying work already in git.

Nothing in the matching flow noticed. It surfaced only because every registry
entry is re-verified through the oracle after a batch, which is why that step
exists. Any future batch must refuse to overwrite an existing source rather than
assume it owns the path.

## Linking: why bytes from the object are not comparable

Until now only relocation-free leaf functions could be matched at all. A
function that calls another, or reads a global, compiles to an object whose
bytes still contain unresolved relocations, so comparing them against retail —
which is fully linked — is meaningless. That excluded the large majority of the
1334 functions.

`build_candidate.py` now links before extracting. The generated script defines
external symbols and places `.text`, then the function's final bytes are cut
from the linked image.

Symbol addresses come from two sources:

1. splat's `config/undefined_syms.auto.txt` and `undefined_funcs.auto.txt`,
   which are already in `name = 0xADDR;` assignment syntax.
2. The symbol name itself, for anything still undefined. splat names
   unidentified symbols after their address, so `func_80042610` resolves to
   `0x80042610`. This is needed because a callee *inside* the split is
   undefined in a single compiled object yet absent from the auto files.

A name carrying no address is reported as an unresolved external rather than
guessed at.

Two details that cost time and are worth keeping:

- **`ld` needs `-EL`.** The toolchain's linker defaults to big-endian MIPS and
  rejects a little-endian object outright.
- **Placement only needs the right 256MB region.** Branches are PC-relative and
  `%hi`/`%lo` carry absolute targets, so neither depends on where a function
  sits. `jal` takes its top four address bits from the delay-slot PC, which is
  the only reason a base address is needed at all.

`build_candidate.py` also clears its output file before building. A failed
build that left the previous run's bytes in place caused `match_function` to
report a confident MATCH on stale data during this work — the exact false pass
the oracle exists to prevent.

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

## Replication achieved on a verified source

The 6→3 elimination is now **replicated**, on stronger evidence than the
original.

`func_80014128` matches retail byte-for-byte, so unlike a work-in-progress
decompilation its C is *known correct*. That changes what a failure means: when
some candidate reproduces retail exactly, any candidate that cannot is
eliminated outright, with no "conditional on the decompilation" caveat.
`discriminate.py` now applies that rule and reports which criterion it used.

| toolchain | PSY-Q | `func_80014128` | verdict |
| --- | --- | --- | --- |
| `gcc-2.6.0-psx` | 3.5 | **100%** | survives |
| `gcc-2.7.2-psx` | 4.0 | **100%** | survives |
| `gcc-2.7.2-cdk-psx` | 4.1 | **100%** | survives |
| `gcc-2.8.0-psx` | 4.3 | 75% | **eliminated** |
| `gcc-2.8.1-psx` | 4.4 | 75% | **eliminated** |
| `gcc-2.91.66-psx` | 4.5 | 75% | **eliminated** |

The elimination set is **identical** to the one `func_80012E6C` produced, from
an independent function using a different criterion. Two functions now agree.

### The concrete difference: the return delay slot

The two words 2.8.x gets wrong are the epilogue, and they are the
return-delay-slot behaviour this document previously could not pin down:

| | word 5 | word 6 | word 7 |
| --- | --- | --- | --- |
| retail, and 2.6.0 / 2.7.2 / 2.7.2-cdk | `addiu $sp, $sp, 0x18` | `jr $ra` | `nop` |
| 2.8.0 / 2.8.1 / 2.91.66 | `nop` | `jr $ra` | `addiu $sp, $sp, 0x18` |

**Retail restores the stack pointer before returning and leaves the return
delay slot empty. The 2.8.x line fills that slot with the restore.** This is the
documented discriminator — 2.8.1 fills the slot after `jr $ra`, 2.7.2 does not —
finally observed in a real function where the scheduling choice is constrained,
rather than in a trivial leaf where it is not.

This also settles the caveat recorded further below. The heuristic is sound; it
simply carries no signal in a function whose delay slot is trivially fillable.

### Still not resolved

`gcc-2.6.0-psx`, `gcc-2.7.2-psx` and `gcc-2.7.2-cdk-psx` all reproduce both
verified functions **exactly**. Nothing separates PSY-Q 3.5 from 4.0 from 4.1
so far, and `func_80012AB0` is non-discriminating for the familiar reason: at
three instructions, all six candidates reproduce it.

Separating the three survivors needs a verified match on a function with enough
register pressure to force allocation choices. The high-pressure candidates are
now reachable thanks to the link step — `func_800346D0` (8 saved registers, 15
distinct) and `func_800435CC` (8 saved, 18 distinct) are the obvious next
targets, but both index arrays of structures and need type modelling before
they will compile.

Per `docs/COMPILER-ID.md` the compiler remains **unresolved**: three candidates
survive, and this is elimination rather than identification.

## Earlier replication attempt: inconclusive

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

**Resolved.** `func_80014128` supplies exactly that constrained case, and the
rule holds there: retail leaves the slot empty and restores `$sp` before
returning, while the 2.8.x line fills the slot with the restore. The heuristic
is sound; the aggregate was simply the wrong way to apply it. See "Replication
achieved on a verified source" above.

## Operational note

`argparse` rejects an option value that looks like a flag, so the optimization
and `-G` arguments must use the `=` form:

```sh
--optimization=-O2 --gp=-G0      # correct
--optimization -O2               # error: expected one argument
```
