/* Exact retail word export for [80061F88,80061F94); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x240a00b0)
MUSASHI_NATIVE_MIPS_WORD(0x01400008)
MUSASHI_NATIVE_MIPS_WORD(0x24090043)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (3/3 words at 0x80061F88). Types and signatures are whatever
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
    ".globl func_80061F88\n"
    ".type func_80061F88, @function\n"
    "func_80061F88:\n"
    "addiu $t2,$zero,0xB0\n"
    "jr $t2\n"
    "addiu $t1,$zero,0x43\n"
    ".size func_80061F88, .-func_80061F88\n"
    ".set reorder\n"
);
#endif
