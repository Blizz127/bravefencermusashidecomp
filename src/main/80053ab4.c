/* Main-exec range [80053AB4,80053AC0) from the SLUS executable.
 * SHA256(span)=e9189e5454ae227c211de6f62fe1f2602ca0d3e8b81e2524c511ba5d4085ec02.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4884F000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AB4\n"
    ".type func_80053AB4, @function\n"
    "func_80053AB4:\n"
    "mtc2 $a0, $30\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AB4, .-func_80053AB4\n"
    ".set reorder\n"
);
#endif
