/* Main-exec range [8004934C,8004936C) from the SLUS executable.
 * SHA256(span)=72234e789d3afcc248b054abf035921eb4c095bb91a156c0df29e023db02b263.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48848800)
MUSASHI_NATIVE_MIPS_WORD(0x48859000)
MUSASHI_NATIVE_MIPS_WORD(0x48869800)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4B58002D)
MUSASHI_NATIVE_MIPS_WORD(0x48023800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004934C\n"
    ".type func_8004934C, @function\n"
    "func_8004934C:\n"
    "mtc2 $a0, $17\n"
    "mtc2 $a1, $18\n"
    "mtc2 $a2, $19\n"
    "nop\n"
    ".word 0x4B58002D\n"
    "mfc2 $v0, $7\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004934C, .-func_8004934C\n"
    ".set reorder\n"
);
#endif
