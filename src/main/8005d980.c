/* Exact retail word export for [8005D980,8005D9C4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24040003)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173D6)
MUSASHI_NATIVE_MIPS_WORD(0x24050001)
MUSASHI_NATIVE_MIPS_WORD(0x3C058008)
MUSASHI_NATIVE_MIPS_WORD(0x24A58988)
MUSASHI_NATIVE_MIPS_WORD(0x0C01785E)
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173C6)
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

void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */
void func_8005CF58(s32, s32);                              /* static */
void func_8005E178(s32, void *);                            /* static */
extern s32 D_80078988;

void func_8005D980(void) {
    func_8005CF08();
    func_8005CF58(3, 1);
    func_8005E178(2, &D_80078988);
    func_8005CF18();
}
#endif
