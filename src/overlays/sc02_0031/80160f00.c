/* SC02.CD FILE_031 / ov_SC02_031 retail span [80160F00,80160F70).
 * Offset 0x38DA8 at overlay base 80128158. SHA256(span)=032510f8282057f1af7c90823267c75fed5b319442df41b7cfa92925feb6a5b4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80160f00.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C052408)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C055054)
MUSASHI_NATIVE_MIPS_WORD(0x24050004)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA42270C0)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A492)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0209A17)
MUSASHI_NATIVE_MIPS_WORD(0x0C051BA4)
MUSASHI_NATIVE_MIPS_WORD(0x24050010)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80129248();                                 /* static */
void func_80146CA0(s32);                               /* static */
void func_80146E90(s32, s32);                            /* static */
void func_80149020();                                  /* static */
void func_80154150(s32, s32);                            /* static */
void func_80154A74(s32, s32);                            /* static */
extern s8 D_800B9A17;
extern s16 D_801270C0;

void func_80160F00(s32 arg0) {
    func_80149020();
    func_80154150(arg0, 4);
    func_80154A74(arg0, 0x11);
    D_801270C0 = 2;
    func_80129248(0);
    D_800B9A17 = 0;
    func_80146E90(arg0, 0x10);
    func_80146CA0(arg0);
}
#endif
