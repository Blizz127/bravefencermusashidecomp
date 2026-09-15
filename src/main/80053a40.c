/* Main-exec range [80053A40,80053A4C) from the SLUS executable.
 * SHA256(span)=96f7dcc76ee52f98f3c538025fe3d5df5f0a5e20df30714924f9f0fc134b2eb3.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48844000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A40\n"
    ".type func_80053A40, @function\n"
    "func_80053A40:\n"
    "mtc2 $a0, $8\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A40, .-func_80053A40\n"
    ".set reorder\n"
);
#endif
