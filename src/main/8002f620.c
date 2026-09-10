/* Exact retail word export [8002F620,8002F648); verified against pinned EXE and asm. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA4204EF0)
MUSASHI_NATIVE_MIPS_WORD(0x0C00C75C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80031D70();                                  /* static */
extern s16 D_800A4EF0;

void func_8002F620(void) {
    D_800A4EF0 = 0;
    func_80031D70();
}

#endif
