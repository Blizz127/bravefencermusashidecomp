/* Main-exec range [800492D8,800492FC) from the SLUS executable.
 * SHA256(span)=91a892c2adb57022e700b10f8801c3726a207157cba716c763b67d4daac4c510.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8890000)
MUSASHI_NATIVE_MIPS_WORD(0xC88A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0008)
MUSASHI_NATIVE_MIPS_WORD(0x48854000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A980011)
MUSASHI_NATIVE_MIPS_WORD(0xE8D60000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800492D8\n"
    ".type func_800492D8, @function\n"
    "func_800492D8:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "mtc2 $a1, $8\n"
    "nop\n"
    ".word 0x4A980011\n"
    "swc2 $22, 0x0($a2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800492D8, .-func_800492D8\n"
    ".set reorder\n"
);
#endif
