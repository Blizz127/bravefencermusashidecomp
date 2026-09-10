#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053ACC\n"
    ".type func_80053ACC, @function\n"
    "func_80053ACC:\n"
    "ctc2 $a0, $28\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053ACC, .-func_80053ACC\n"
    ".set reorder\n"
);
