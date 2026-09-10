#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800495EC\n"
    ".type func_800495EC, @function\n"
    "func_800495EC:\n"
    "mtc2 $a0, $12\n"
    "mtc2 $a2, $14\n"
    "mtc2 $a1, $13\n"
    "nop\n"
    "nop\n"
    ".word 0x4B400006\n"
    "mfc2 $v0, $24\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800495EC, .-func_800495EC\n"
    ".set reorder\n"
);
