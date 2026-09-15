/* Main-exec range [800491CC,800491EC) from the SLUS executable.
 * SHA256(span)=2f9e759091975bad3585277ae26c3eb50addd764857351a5213c14fb2c857a89.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4848C000)
MUSASHI_NATIVE_MIPS_WORD(0x4849C800)
MUSASHI_NATIVE_MIPS_WORD(0x00084403)
MUSASHI_NATIVE_MIPS_WORD(0x00094C03)
MUSASHI_NATIVE_MIPS_WORD(0xAC880000)
MUSASHI_NATIVE_MIPS_WORD(0xACA90000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491CC\n"
    ".type func_800491CC, @function\n"
    "func_800491CC:\n"
    "cfc2 $t0, $24\n"
    "cfc2 $t1, $25\n"
    "sra $t0, $t0, 16\n"
    "sra $t1, $t1, 16\n"
    "sw $t0, 0x0($a0)\n"
    "sw $t1, 0x0($a1)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491CC, .-func_800491CC\n"
    ".set reorder\n"
);
#endif
