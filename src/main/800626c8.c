/* Exact retail word export for [800626C8,800626DC); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c098008)
MUSASHI_NATIVE_MIPS_WORD(0x8d298d20)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x01200008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (5/5 words at 0x800626C8). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

/* BIOS vector thunk: the tail jump goes through a register that is not
 * $ra, leaving the call number in another register for the vector to
 * read. C emits jalr for an indirect call, so it cannot spell this.
 * NOT verified against retail; promotion requires an oracle MATCH
 * (tools/match_function.py). */
__asm__(
    ".set noreorder\n"
    ".globl func_800626C8\n"
    ".type func_800626C8, @function\n"
    "func_800626C8:\n"
    "lui $t1,%hi(jtbl_80078D20_main)\n"
    "lw $t1,%lo(jtbl_80078D20_main)($t1)\n"
    "nop\n"
    "jr $t1\n"
    "nop\n"
    ".size func_800626C8, .-func_800626C8\n"
    ".set reorder\n"
);
#endif
