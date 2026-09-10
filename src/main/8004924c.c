#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004924C\n"
    ".type func_8004924C, @function\n"
    "func_8004924C:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "nop\n"
    ".word 0x4A4DA412\n"
    "swc2 $9, 0x0($a1)\n"
    "swc2 $10, 0x4($a1)\n"
    "swc2 $11, 0x8($a1)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004924C, .-func_8004924C\n"
    ".set reorder\n"
);
