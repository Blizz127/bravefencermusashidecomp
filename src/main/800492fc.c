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
