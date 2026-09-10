#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A2C\n"
    ".type func_80053A2C, @function\n"
    "func_80053A2C:\n"
    "mtc2 $a0, $9\n"
    "mtc2 $a1, $10\n"
    "mtc2 $a2, $11\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A2C, .-func_80053A2C\n"
    ".set reorder\n"
);
