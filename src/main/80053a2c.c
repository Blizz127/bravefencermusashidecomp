/* Main-exec range [80053A2C,80053A40) from the SLUS executable.
 * SHA256(span)=6da9cf831c0db5d80eb5999464d1f03a4f775f37cc586406f93adc036b942b79.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48844800)
MUSASHI_NATIVE_MIPS_WORD(0x48855000)
MUSASHI_NATIVE_MIPS_WORD(0x48865800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A2C\n"
    ".type func_80053A2C, @function\n"
    "func_80053A2C:\n"
    "mtc2 $a0, $9\n"
    "mtc2 $a1, $10\n"
    "mtc2 $a2, $11\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A2C, .-func_80053A2C\n"
    ".set reorder\n"
);
#endif
