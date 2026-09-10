/* Exact retail word export for [800538BC,800538EC); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C880000)
MUSASHI_NATIVE_MIPS_WORD(0x8C890004)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C8B000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C8C0010)
MUSASHI_NATIVE_MIPS_WORD(0x48C88000)
MUSASHI_NATIVE_MIPS_WORD(0x48C98800)
MUSASHI_NATIVE_MIPS_WORD(0x48CA9000)
MUSASHI_NATIVE_MIPS_WORD(0x48CB9800)
MUSASHI_NATIVE_MIPS_WORD(0x48CCA000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800538BC\n"
    ".type func_800538BC, @function\n"
    "func_800538BC:\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "lw $t3, 0xC($a0)\n"
    "lw $t4, 0x10($a0)\n"
    "ctc2 $t0, $16\n"
    "ctc2 $t1, $17\n"
    "ctc2 $t2, $18\n"
    "ctc2 $t3, $19\n"
    "ctc2 $t4, $20\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800538BC, .-func_800538BC\n"
    ".set reorder\n"
);
#endif
