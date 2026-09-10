#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A4C\n"
    ".type func_80053A4C, @function\n"
    "func_80053A4C:\n"
    "mtc2 $a0, $17\n"
    "mtc2 $a1, $18\n"
    "mtc2 $a2, $19\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A4C, .-func_80053A4C\n"
    ".set reorder\n"
);
