#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A78\n"
    ".type func_80053A78, @function\n"
    "func_80053A78:\n"
    "mtc2 $a0, $12\n"
    "mtc2 $a1, $13\n"
    "mtc2 $a2, $14\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A78, .-func_80053A78\n"
    ".set reorder\n"
);
