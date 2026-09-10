#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xC8800000)
MUSASHI_NATIVE_MIPS_WORD(0xC8810004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4A480012)
MUSASHI_NATIVE_MIPS_WORD(0x48024800)
MUSASHI_NATIVE_MIPS_WORD(0x48035000)
MUSASHI_NATIVE_MIPS_WORD(0xE8AB0004)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A30002)
MUSASHI_NATIVE_MIPS_WORD(0x4842F800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACC20000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004945C\n"
    ".type func_8004945C, @function\n"
    "func_8004945C:\n"
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "nop\n"
    ".word 0x4A480012\n"
    "mfc2 $v0, $9\n"
    "mfc2 $v1, $10\n"
    "swc2 $11, 0x4($a1)\n"
    "sh $v0, 0x0($a1)\n"
    "sh $v1, 0x2($a1)\n"
    "cfc2 $v0, $31\n"
    "jr $ra\n"
    "sw $v0, 0x0($a2)\n"
    ".size func_8004945C, .-func_8004945C\n"
    ".set reorder\n"
);
#endif
