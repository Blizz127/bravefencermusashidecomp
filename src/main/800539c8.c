#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800539C8\n"
    ".type func_800539C8, @function\n"
    "func_800539C8:\n"
    "lwc2 $0, 0x0($a0)\n"
    "lwc2 $1, 0x4($a0)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800539C8, .-func_800539C8\n"
    ".set reorder\n"
);
