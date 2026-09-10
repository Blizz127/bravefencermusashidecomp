#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C880014)
MUSASHI_NATIVE_MIPS_WORD(0x8C890018)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A001C)
MUSASHI_NATIVE_MIPS_WORD(0x48C82800)
MUSASHI_NATIVE_MIPS_WORD(0x48C93000)
MUSASHI_NATIVE_MIPS_WORD(0x48CA3800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* GTE/cop2 mnemonic overlay: ordinary C cannot emit coprocessor ops.
 * Verified by tools/match_function.py. */
__asm__(
    ".set noreorder\n"
    ".globl func_800491AC\n"
    ".type func_800491AC, @function\n"
    "func_800491AC:\n"
    "lw $t0, 0x14($a0)\n"
    "lw $t1, 0x18($a0)\n"
    "lw $t2, 0x1C($a0)\n"
    "ctc2 $t0, $5\n"
    "ctc2 $t1, $6\n"
    "ctc2 $t2, $7\n"
    "jr $ra\n"
    "nop\n"
    ".size func_800491AC, .-func_800491AC\n"
    ".set reorder\n"
);
#endif
