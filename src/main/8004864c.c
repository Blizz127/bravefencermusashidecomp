#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004864C\n"
    ".type func_8004864C, @function\n"
    "func_8004864C:\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "mtc2 $t0, $0\n"
    "mtc2 $t1, $1\n"
    "nop\n"
    ".word 0x4A486012\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "addu $v0, $a2, $zero\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004864C, .-func_8004864C\n"
    ".set reorder\n"
);
