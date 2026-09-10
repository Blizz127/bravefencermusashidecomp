/* Exact retail word export for [8004923C,80049248); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x48c4d000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_8004923C\n"
    ".type func_8004923C, @function\n"
    "func_8004923C:\n"
    "ctc2 $a0, $26\n"
    "jr $ra\n"
    "nop\n"
    ".size func_8004923C, .-func_8004923C\n"
    ".set reorder\n"
);
#endif
