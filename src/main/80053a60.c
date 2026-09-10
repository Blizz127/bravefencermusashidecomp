#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A60\n"
    ".type func_80053A60, @function\n"
    "func_80053A60:\n"
    "mtc2 $a0, $16\n"
    "mtc2 $a1, $17\n"
    "mtc2 $a2, $18\n"
    "mtc2 $a3, $19\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A60, .-func_80053A60\n"
    ".set reorder\n"
);
