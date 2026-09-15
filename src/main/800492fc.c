/* Main-exec range [800492FC,80049324) from the SLUS executable.
 * SHA256(span)=8eb49b1a6805d4a218b9a35c2f9ab81c8cb702b3ced2c46674284158713c5aaf.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8890000)
MUSASHI_NATIVE_MIPS_WORD(0xC88A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4AA80428)
MUSASHI_NATIVE_MIPS_WORD(0xE8B90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8BA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8BB0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800492FC\n"
    ".type func_800492FC, @function\n"
    "func_800492FC:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "nop\n"
    ".word 0x4AA80428\n"
    "swc2 $25, 0x0($a1)\n"
    "swc2 $26, 0x4($a1)\n"
    "swc2 $27, 0x8($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_800492FC, .-func_800492FC\n"
    ".set reorder\n"
);
#endif
