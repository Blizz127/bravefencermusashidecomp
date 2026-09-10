/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013CB5C,8013CB84).
 * Offset 0x14A04 at overlay base 80128158. SHA256(span)=ebed26ce20ef1975101b999459e80c1919f9b4bba2ee2ba8644fd9dbe25a3861.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_801841BC->D_801A44E4; D_801841C0->D_801A44E8; D_801841E8->D_801A4510; D_801841EC->D_801A4514.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801A)
MUSASHI_NATIVE_MIPS_WORD(0x8C424510)
MUSASHI_NATIVE_MIPS_WORD(0x3C03801A)
MUSASHI_NATIVE_MIPS_WORD(0x8C634514)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2244E8)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2344E4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801A44E4;
extern s32 D_801A44E8;
extern s32 D_801A4510;
extern s32 D_801A4514;

void func_8013CB5C(void) {
    D_801A44E8 = (s32) D_801A4510;
    D_801A44E4 = (s32) D_801A4514;
}

#endif
