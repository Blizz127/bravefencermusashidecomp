/* Main-exec range [800495EC,80049610) from the SLUS executable.
 * SHA256(span)=9b05fe5b9d5d7a6655357b6380c317b55990b52c4f8a8cc129ed5b7fc89e5d3b.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48846000)
MUSASHI_NATIVE_MIPS_WORD(0x48867000)
MUSASHI_NATIVE_MIPS_WORD(0x48856800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4B400006)
MUSASHI_NATIVE_MIPS_WORD(0x4802C000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800495EC\n"
    ".type func_800495EC, @function\n"
    "func_800495EC:\n"
    "mtc2 $a0, $12\n"
    "mtc2 $a2, $14\n"
    "mtc2 $a1, $13\n"
    "nop\n"
    "nop\n"
    ".word 0x4B400006\n"
    "mfc2 $v0, $24\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800495EC, .-func_800495EC\n"
    ".set reorder\n"
);
#endif
