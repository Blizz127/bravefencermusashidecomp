/* Main-exec range [800539C8,800539D8) from the SLUS executable.
 * SHA256(span)=8901c82b29e97a0872c9fd5622f44111796ce9318a26a18975ce2f078be0889a.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8800000)
MUSASHI_NATIVE_MIPS_WORD(0xC8810004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539C8\n"
    ".type func_800539C8, @function\n"
    "func_800539C8:\n"
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539C8, .-func_800539C8\n"
    ".set reorder\n"
);
#endif
