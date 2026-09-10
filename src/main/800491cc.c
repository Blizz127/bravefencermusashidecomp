#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491CC\n"
    ".type func_800491CC, @function\n"
    "func_800491CC:\n"
    "cfc2 $t0, $24\n"
    "cfc2 $t1, $25\n"
    "sra $t0, $t0, 16\n"
    "sra $t1, $t1, 16\n"
    "sw $t0, 0x0($a0)\n"
    "sw $t1, 0x0($a1)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491CC, .-func_800491CC\n"
    ".set reorder\n"
);
