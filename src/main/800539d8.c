#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539D8\n"
    ".type func_800539D8, @function\n"
    "func_800539D8:\n"
    "lwc2 $2, 0x0($a0)\n"
    "lwc2 $3, 0x4($a0)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539D8, .-func_800539D8\n"
    ".set reorder\n"
);
