/* Main-exec range [80053A18,80053A2C) from the SLUS executable.
 * SHA256(span)=ad199cbaca41bcea007b37230fbf5b5b4d7564f69951259361790ac0a5b136cb.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8940000)
MUSASHI_NATIVE_MIPS_WORD(0xC8B50000)
MUSASHI_NATIVE_MIPS_WORD(0xC8D60000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A18\n"
    ".type func_80053A18, @function\n"
    "func_80053A18:\n"
    "lwc2 $20, 0x0($a0)\n"
    "lwc2 $21, 0x0($a1)\n"
    "lwc2 $22, 0x0($a2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A18, .-func_80053A18\n"
    ".set reorder\n"
);
#endif
