#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800492D8\n"
    ".type func_800492D8, @function\n"
    "func_800492D8:\n"
    "lwc2 $9, 0x0($a0)\n"
    "lwc2 $10, 0x4($a0)\n"
    "lwc2 $11, 0x8($a0)\n"
    "mtc2 $a1, $8\n"
    "nop\n"
    ".word 0x4A980011\n"
    "swc2 $22, 0x0($a2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800492D8, .-func_800492D8\n"
    ".set reorder\n"
);
