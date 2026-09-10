#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AC0\n"
    ".type func_80053AC0, @function\n"
    "func_80053AC0:\n"
    "ctc2 $a0, $27\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AC0, .-func_80053AC0\n"
    ".set reorder\n"
);
