#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c011f2d)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0c014eb6)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c012487)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xa420654a)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xa4206548)
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

void func_80047CB4();                                  /* static */
void func_8004921C(s32, s32);                              /* static */
void func_80053AD8(s32, s32, s32);                           /* static */
extern s16 D_800A6548;
extern s16 D_800A654A;

void func_80053CF8(void) {
    func_80047CB4();
    func_80053AD8(0, 0, 0);
    func_8004921C(0, 0);
    D_800A654A = 0;
    D_800A6548 = 0;
}
#endif
