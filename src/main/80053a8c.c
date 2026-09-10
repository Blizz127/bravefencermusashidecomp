#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A8C\n"
    ".type func_80053A8C, @function\n"
    "func_80053A8C:\n"
    "ctc2 $a0, $0\n"
    "ctc2 $a1, $2\n"
    "ctc2 $a2, $4\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A8C, .-func_80053A8C\n"
    ".set reorder\n"
);
