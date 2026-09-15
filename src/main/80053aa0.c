/* Main-exec range [80053AA0,80053AB4) from the SLUS executable.
 * SHA256(span)=54b7eeb51ac9b243c2caf48a078814305b17ea82899ad749dc26ca4c547f5cbd.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4884C800)
MUSASHI_NATIVE_MIPS_WORD(0x4885D000)
MUSASHI_NATIVE_MIPS_WORD(0x4886D800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AA0\n"
    ".type func_80053AA0, @function\n"
    "func_80053AA0:\n"
    "mtc2 $a0, $25\n"
    "mtc2 $a1, $26\n"
    "mtc2 $a2, $27\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AA0, .-func_80053AA0\n"
    ".set reorder\n"
);
#endif
