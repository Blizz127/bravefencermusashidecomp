#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491EC\n"
    ".type func_800491EC, @function\n"
    "func_800491EC:\n"
    "cfc2 $v0, $26\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491EC, .-func_800491EC\n"
    ".set reorder\n"
);
