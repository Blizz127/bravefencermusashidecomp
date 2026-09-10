#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x4884F000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x4802F800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_80049440\n"
    ".type func_80049440, @function\n"
    "func_80049440:\n"
    "mtc2 $a0, $30\n"
    "nop\n"
    "nop\n"
    "mfc2 $v0, $31\n"
    "jr $ra\n"
    "nop\n"
    ".size func_80049440, .-func_80049440\n"
    ".set reorder\n"
);
#endif
