/* Main-exec range [80053A4C,80053A60) from the SLUS executable.
 * SHA256(span)=8087d1ed7c27a56546edfc5eb90c889963430f3eeccaf702df663c181854fcbd.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48848800)
MUSASHI_NATIVE_MIPS_WORD(0x48859000)
MUSASHI_NATIVE_MIPS_WORD(0x48869800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A4C\n"
    ".type func_80053A4C, @function\n"
    "func_80053A4C:\n"
    "mtc2 $a0, $17\n"
    "mtc2 $a1, $18\n"
    "mtc2 $a2, $19\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A4C, .-func_80053A4C\n"
    ".set reorder\n"
);
#endif
