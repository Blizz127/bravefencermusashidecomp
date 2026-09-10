/* Exact retail word export for [800525DC,80052654); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffd8)
MUSASHI_NATIVE_MIPS_WORD(0xafb1001c)
MUSASHI_NATIVE_MIPS_WORD(0x3091ffff)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0xafb00018)
MUSASHI_NATIVE_MIPS_WORD(0x30b0ffff)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x30c6ffff)
MUSASHI_NATIVE_MIPS_WORD(0x97a20038)
MUSASHI_NATIVE_MIPS_WORD(0x30e7ffff)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0020)
MUSASHI_NATIVE_MIPS_WORD(0x0c014995)
MUSASHI_NATIVE_MIPS_WORD(0xafa20010)
MUSASHI_NATIVE_MIPS_WORD(0x0c014f3e)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0xa4207c74)
MUSASHI_NATIVE_MIPS_WORD(0x0c014a0f)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x0c014b40)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c014afb)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0020)
MUSASHI_NATIVE_MIPS_WORD(0x8fb1001c)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00018)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0028)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80052654(s32, s32, s32, s32, s32);           /* static */
void func_8005283C(s32, s32);                          /* static */
void func_80052BEC();                                  /* static */
void func_80052D00();                                  /* static */
void func_80053CF8();                                  /* static */
extern s16 D_800C7C74;

void func_800525DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = arg0 & 0xFFFF;
    temp_s0 = arg1 & 0xFFFF;
    func_80052654(temp_s1, temp_s0, arg2 & 0xFFFF, arg3 & 0xFFFF, (s32) arg4);
    func_80053CF8();
    D_800C7C74 = 0;
    func_8005283C(temp_s1, temp_s0);
    func_80052D00();
    func_80052BEC();
}
#endif
