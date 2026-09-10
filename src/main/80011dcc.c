/* Exact retail word export [80011DCC,80011DF4); verified against pinned EXE and asm. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0000)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC204780)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 D_80074780;

void func_80011DCC(void) {
    D_80074780 = 0;
}

#endif
