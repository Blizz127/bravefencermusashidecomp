/* Exact retail word export for [80053AD8,80053AF8); EXE/asm verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00042100)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x00063100)
MUSASHI_NATIVE_MIPS_WORD(0x48c4a800)
MUSASHI_NATIVE_MIPS_WORD(0x48c5b000)
MUSASHI_NATIVE_MIPS_WORD(0x48c6b800)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80053AD8\n"
    ".type func_80053AD8, @function\n"
    "func_80053AD8:\n"
    "sll $a0, $a0, 4\n"
    "sll $a1, $a1, 4\n"
    "sll $a2, $a2, 4\n"
    "ctc2 $a0, $21\n"
    "ctc2 $a1, $22\n"
    "ctc2 $a2, $23\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80053AD8, .-func_80053AD8\n"
    ".set reorder\n"
);
#endif
