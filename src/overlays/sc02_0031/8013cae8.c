/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013CAE8,8013CB20).
 * Offset 0x14990 at overlay base 80128158. SHA256(span)=6183e61dc01da7a5a1694b909936e165b1b74ecd00315ab77540302b2ac11db5.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_801841B0->D_801A44D8; D_801841B4->D_801A44DC; D_801841B8->D_801A44E0; D_801841BC->D_801A44E4; D_801841C0->D_801A44E8.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2244D8)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2044E4)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2044DC)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2244E0)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2044E8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801A44D8;
extern s32 D_801A44DC;
extern s32 D_801A44E0;
extern s32 D_801A44E4;
extern s32 D_801A44E8;

void func_8013CAE8(void) {
    D_801A44D8 = 1;
    D_801A44E4 = 0;
    D_801A44DC = 0;
    D_801A44E0 = -1;
    D_801A44E8 = 0;
}

#endif
