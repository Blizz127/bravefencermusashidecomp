#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004948C\n"
    ".type func_8004948C, @function\n"
    "func_8004948C:\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x2($a0)\n"
    "mtc2 $v0, $9\n"
    "mtc2 $v1, $10\n"
    "lwc2 $11, 0x4($a0)\n"
    "nop\n"
    ".word 0x4AA80428\n"
    "mfc2 $v0, $9\n"
    "mfc2 $v1, $10\n"
    "swc2 $11, 0x4($a1)\n"
    "sh $v0, 0x0($a1)\n"
    "sh $v1, 0x2($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_8004948C, .-func_8004948C\n"
    ".set reorder\n"
);
