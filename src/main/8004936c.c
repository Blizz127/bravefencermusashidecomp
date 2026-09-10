#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004936C\n"
    ".type func_8004936C, @function\n"
    "func_8004936C:\n"
    "mtc2 $a0, $16\n"
    "mtc2 $a1, $17\n"
    "mtc2 $a2, $18\n"
    "mtc2 $a3, $19\n"
    "nop\n"
    ".word 0x4B68002E\n"
    "mfc2 $v0, $7\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004936C, .-func_8004936C\n"
    ".set reorder\n"
);
