/* Main-exec range [80053A78,80053A8C) from the SLUS executable.
 * SHA256(span)=d1fe526732bfbe89e5afe1854f4b849aec907632f3461a18034aef3597b2a456.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48846000)
MUSASHI_NATIVE_MIPS_WORD(0x48856800)
MUSASHI_NATIVE_MIPS_WORD(0x48867000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A78\n"
    ".type func_80053A78, @function\n"
    "func_80053A78:\n"
    "mtc2 $a0, $12\n"
    "mtc2 $a1, $13\n"
    "mtc2 $a2, $14\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A78, .-func_80053A78\n"
    ".set reorder\n"
);
#endif
