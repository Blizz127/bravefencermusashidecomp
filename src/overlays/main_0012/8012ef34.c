#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8012EF34\n"
    ".type func_8012EF34, @function\n"
    "func_8012EF34:\n"
    "addiu $sp, $sp, -0x20\n"
    "sw $s0, 0x18($sp)\n"
    "sw $ra, 0x1C($sp)\n"
    ".word 0x0C04BBEE\n"
    "addu $s0, $a1, $zero\n"
    "addiu $v1, $sp, 0x10\n"
    "swc2 $19, 0x0($v1)\n"
    "lw $v1, 0x10($sp)\n"
    "nop\n"
    "sh $v1, 0x4($s0)\n"
    "lw $ra, 0x1C($sp)\n"
    "lw $s0, 0x18($sp)\n"
    "addiu $sp, $sp, 0x20\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8012EF34, .-func_8012EF34\n"
    ".set reorder\n"
);
