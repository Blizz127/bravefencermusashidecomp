#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004952C\n"
    ".type func_8004952C, @function\n"
    "func_8004952C:\n"
    "lh $v0, 0x0($a0)\n"
    "lh $v1, 0x2($a0)\n"
    "mtc2 $v0, $9\n"
    "mtc2 $v1, $10\n"
    "lwc2 $11, 0x4($a0)\n"
    "nop\n"
    ".word 0x4AA00428\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "jr $ra\n"
    "addu $v0, $a1, $zero\n"
    ".size func_8004952C, .-func_8004952C\n"
    ".set reorder\n"
);
