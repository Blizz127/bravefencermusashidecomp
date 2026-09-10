#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A40\n"
    ".type func_80053A40, @function\n"
    "func_80053A40:\n"
    "mtc2 $a0, $8\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A40, .-func_80053A40\n"
    ".set reorder\n"
);
