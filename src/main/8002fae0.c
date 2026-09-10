/* Exact retail word export for [8002FAE0,8002FB08); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xa42046cc)
MUSASHI_NATIVE_MIPS_WORD(0x0c00b22f)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8002C8BC();                                  /* static */
extern s16 D_800A46CC;

void func_8002FAE0(void) {
    D_800A46CC = 0;
    func_8002C8BC();
}
#endif
