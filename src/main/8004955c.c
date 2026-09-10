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
