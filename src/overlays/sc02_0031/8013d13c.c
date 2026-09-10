/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013D13C,8013D164).
 * Offset 0x14FE4 at overlay base 80128158. SHA256(span)=62fad90c158d9ca891af81eb1a4964c11c10b38401be4d5bde81dee5242442fd.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_801841BC->D_801A44E4.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F66C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02801A)
MUSASHI_NATIVE_MIPS_WORD(0x8C4244E4)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801A44E4;
void func_8013D9B0();                                  /* static */

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801A44E4;
}

#endif
