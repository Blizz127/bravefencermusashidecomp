#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AA0\n"
    ".type func_80053AA0, @function\n"
    "func_80053AA0:\n"
    "mtc2 $a0, $25\n"
    "mtc2 $a1, $26\n"
    "mtc2 $a2, $27\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AA0, .-func_80053AA0\n"
    ".set reorder\n"
);
