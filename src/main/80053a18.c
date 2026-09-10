#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053A18\n"
    ".type func_80053A18, @function\n"
    "func_80053A18:\n"
    "lwc2 $20, 0x0($a0)\n"
    "lwc2 $21, 0x0($a1)\n"
    "lwc2 $22, 0x0($a2)\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053A18, .-func_80053A18\n"
    ".set reorder\n"
);
