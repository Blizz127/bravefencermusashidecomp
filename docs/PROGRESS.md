# Interpreting progress

`python3 tools/progress.py` reports registered byte ranges and sums their sizes.
It also reports unique qualifying coverage: the overlap-union of complete
functions (`extent` `function`) recovered as reviewed `c` or `assembly`,
counted once per region, against the identified split-code denominator
(SLUS_007.26 `t_size` 411648 + MAIN.CD member 0007 9600 + member 0012 code
chunk `[0x28000, 0x86000)` 385024 = 806272 bytes). The 30% bar is 241882
unique qualifying bytes. `partial`/`unclassified`/`mixed` rows and
non-function extents are excluded from that numerator.

It reads claims from `provenance/matches.json`; it does not compile or compare
anything. Run `python3 tools/verify_registry.py` to re-earn the byte matches.
Summed sizes are not a union of covered addresses or a percentage of the game.

The old report called every entry a function rebuilt from C. That is incorrect:
for example, `src/main/800100a0.c` contains an assembly implementation of the
constructor guard. A `.c` suffix, a matching binary, or a range larger than eight
bytes does not prove C recovery, function completeness, or native portability.

Optional fields on each match record make reviewed classifications explicit:

| Field | Values | Meaning |
| --- | --- | --- |
| `recovery` | `c`, `assembly`, `mixed`, `unclassified` | Implementation producing the matched range |
| `extent` | `function`, `partial`, `unclassified` | Whether the range covers the complete identified function |

Missing fields default to `unclassified`; invalid values are refused.
Classification is a reviewed claim, not something the reporting tool verifies.
Before setting fields, inspect the exact source/configuration producing the
range and the retail control-flow boundaries. Embedded native word exports
alone do not classify the separately compiled PS1 implementation. Empty compiler
constraints alone do not turn a C implementation into assembly transcription.
An assembly implementation does not establish original handwritten provenance.
An interior label or prefix must not be called a complete function simply
because the matching harness can export it. Keep uncertain cases unclassified.

Initial reviewed entries were `80012AB0` (12 bytes, C function) and `800100A0`
(112 bytes, assembly function). Subsequent review and fresh byte comparisons
classified `800429DC` (340 bytes), `80042F8C` (168 bytes), and their dispatch
wrappers `800425B0` and `800425E0` (48 bytes each) as complete C functions
while binding their shared bodies to the native port. Other existing
entries have deliberately not been assigned bulk classifications. The same
review subsequently classified `80042CE8` (120 bytes) as a complete C function
when binding its live-slot handler to guest RAM.
The retail-observed VBlank callback `800616D0` (160 bytes) and its direct helpers
`8006291C` (108 bytes) and `80062988` (16 bytes) were subsequently recovered,
byte-verified, and registered as C functions. Their shared native bindings now
execute through the VBlank slot router, with external request/completion calls
requiring checked execution. This does not establish interrupt delivery.
Unclassified does not revoke their byte
matches; it keeps the recovery audit visibly incomplete. Instruction fragments
outside the registry, such as `80044670_prefix.c`, are not added to these totals.

The source and extent totals are independent; a C range may still be partial.
None of these figures proves native startup, an interactive menu, or full retail
parity. The historical `function_count`, `trivial_count`, and `substantive_count`
Python summary keys remain for existing callers, but mean range count and the
two size buckets only. The command-line output uses those accurate labels.
