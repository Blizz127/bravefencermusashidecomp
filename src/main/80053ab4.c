#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AB4\n"
    ".type func_80053AB4, @function\n"
    "func_80053AB4:\n"
    "mtc2 $a0, $30\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AB4, .-func_80053AB4\n"
    ".set reorder\n"
);
