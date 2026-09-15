/* Main-exec range [800140B8,80014128) from the SLUS executable.
 * SHA256(span)=d4176183f4b724de905835147a894749eb9abe9055ccf6b9c9bbf82ba60d6243.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8C0000)
MUSASHI_NATIVE_MIPS_WORD(0x8C8D0004)
MUSASHI_NATIVE_MIPS_WORD(0x48CC0000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD0800)
MUSASHI_NATIVE_MIPS_WORD(0x8C8C0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C8D000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C8E0010)
MUSASHI_NATIVE_MIPS_WORD(0x48CC1000)
MUSASHI_NATIVE_MIPS_WORD(0x48CD1800)
MUSASHI_NATIVE_MIPS_WORD(0x48CE2000)
MUSASHI_NATIVE_MIPS_WORD(0xC8A00000)
MUSASHI_NATIVE_MIPS_WORD(0xC8A10004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A486012)
MUSASHI_NATIVE_MIPS_WORD(0xE8D90000)
MUSASHI_NATIVE_MIPS_WORD(0xE8DA0004)
MUSASHI_NATIVE_MIPS_WORD(0xE8DB0008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0xACC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20004)
MUSASHI_NATIVE_MIPS_WORD(0x00031C00)
MUSASHI_NATIVE_MIPS_WORD(0xACC30008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACC20004)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800140B8\n"
    ".type func_800140B8, @function\n"
    "func_800140B8:\n"
    "lw $t4, 0x0($a0)\n"
    "lw $t5, 0x4($a0)\n"
    "ctc2 $t4, $0\n"
    "ctc2 $t5, $1\n"
    "lw $t4, 0x8($a0)\n"
    "lw $t5, 0xC($a0)\n"
    "lw $t6, 0x10($a0)\n"
    "ctc2 $t4, $2\n"
    "ctc2 $t5, $3\n"
    "ctc2 $t6, $4\n"
    "lwc2 $0, 0x0($a1)\n"
    "lwc2 $1, 0x4($a1)\n"
    "nop\n"
    "nop\n"
    ".word 0x4A486012\n"
    "swc2 $25, 0x0($a2)\n"
    "swc2 $26, 0x4($a2)\n"
    "swc2 $27, 0x8($a2)\n"
    "lw $v0, 0x0($a2)\n"
    "lw $v1, 0x8($a2)\n"
    "sll $v0, $v0, 16\n"
    "sw $v0, 0x0($a2)\n"
    "lw $v0, 0x4($a2)\n"
    "sll $v1, $v1, 16\n"
    "sw $v1, 0x8($a2)\n"
    "sll $v0, $v0, 16\n"
    "jr $ra\n"
    "sw $v0, 0x4($a2)\n"
    ".size func_800140B8, .-func_800140B8\n"
    ".set reorder\n"
);
#endif
