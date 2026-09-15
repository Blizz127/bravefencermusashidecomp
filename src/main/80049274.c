/* Main-exec range [80049274,8004929C) from the SLUS executable.
 * SHA256(span)=a9fd370295eb8d79a4f5a8803c448bec1ea52cb588cfa1b044c8278438f9d470.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8890000)
MUSASHI_NATIVE_MIPS_WORD(0xC88A0004)
MUSASHI_NATIVE_MIPS_WORD(0xC88B0008)
MUSASHI_NATIVE_MIPS_WORD(0xC8A60000)
MUSASHI_NATIVE_MIPS_WORD(0x48864000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A680029)
MUSASHI_NATIVE_MIPS_WORD(0xE8F60000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80049274\n"
    ".type func_80049274, @function\n"
    "func_80049274:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "lwc2 $6, 0x0($a1)\n"
    "mtc2 $a2, $8\n"
    "nop\n"
    ".word 0x4A680029\n"
    "swc2 $22, 0x0($a3)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80049274, .-func_80049274\n"
    ".set reorder\n"
);
#endif
