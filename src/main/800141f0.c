#include "psx_types.h"

/* Exact matched entry stream for the bounded native MIPS diagnostic. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c01648d)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c016533)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c016596)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3c04800c)
MUSASHI_NATIVE_MIPS_WORD(0x2484a118)
MUSASHI_NATIVE_MIPS_WORD(0x0c0059c5)
MUSASHI_NATIVE_MIPS_WORD(0x24050098)
MUSASHI_NATIVE_MIPS_WORD(0x0c0050b2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800142C8();                                  /* static */
void func_80016714(void *, s32);                            /* static */
void func_80059234();                                 /* static */
void func_800594CC();                                 /* static */
void func_80059658();                                 /* static */
extern s32 D_800BA118;

void func_800141F0(void) {
    func_80059234(0);
    func_800594CC(0);
    func_80059658(0);
    func_80016714(&D_800BA118, 0x98);
    func_800142C8();
}
