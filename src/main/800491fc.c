/* Exact retail word export for [800491FC,8004921C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00042100)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x00063100)
MUSASHI_NATIVE_MIPS_WORD(0x48C46800)
MUSASHI_NATIVE_MIPS_WORD(0x48C57000)
MUSASHI_NATIVE_MIPS_WORD(0x48C67800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491FC\n"
    ".type func_800491FC, @function\n"
    "func_800491FC:\n"
    "sll $a0, $a0, 4\n"
    "sll $a1, $a1, 4\n"
    "sll $a2, $a2, 4\n"
    "ctc2 $a0, $13\n"
    "ctc2 $a1, $14\n"
    "ctc2 $a2, $15\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491FC, .-func_800491FC\n"
    ".set reorder\n"
);
#endif
