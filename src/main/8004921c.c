/* Exact retail word export for [8004921C,80049234); EXE/asm verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00042400)
MUSASHI_NATIVE_MIPS_WORD(0x00052c00)
MUSASHI_NATIVE_MIPS_WORD(0x48c4c000)
MUSASHI_NATIVE_MIPS_WORD(0x48c5c800)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004921C\n"
    ".type func_8004921C, @function\n"
    "func_8004921C:\n"
    "sll $a0, $a0, 16\n"
    "sll $a1, $a1, 16\n"
    "ctc2 $a0, $24\n"
    "ctc2 $a1, $25\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004921C, .-func_8004921C\n"
    ".set reorder\n"
);
#endif
