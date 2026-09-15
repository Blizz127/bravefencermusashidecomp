/* Main-exec range [8004955C,80049588) from the SLUS executable.
 * SHA256(span)=bfea6684241144708ce8aaa4e9bc56b0c2851fe6229be220a3d007d86230d878.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8800000)
MUSASHI_NATIVE_MIPS_WORD(0xC8810004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A180001)
MUSASHI_NATIVE_MIPS_WORD(0xE8AE0000)
MUSASHI_NATIVE_MIPS_WORD(0xE8C80000)
MUSASHI_NATIVE_MIPS_WORD(0x4843F800)
MUSASHI_NATIVE_MIPS_WORD(0x48029800)
MUSASHI_NATIVE_MIPS_WORD(0xACE30000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004955C\n"
    ".type func_8004955C, @function\n"
    "func_8004955C:\n"
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "nop\n"
    ".word 0x4A180001\n"
    "swc2 $14, 0x0($a1)\n"
    "swc2 $8, 0x0($a2)\n"
    "cfc2 $v1, $31\n"
    "mfc2 $v0, $19\n"
    "sw $v1, 0x0($a3)\n"
    "jr $ra\n"
    "sra $v0, $v0, 2\n"
    ".size func_8004955C, .-func_8004955C\n"
    ".set reorder\n"
);
#endif
