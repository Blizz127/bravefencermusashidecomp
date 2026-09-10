/* SC02.CD FILE_031 / ov_SC02_031 retail span [80160B00,80160B34).
 * Offset 0x389A8 at overlay base 80128158. SHA256(span)=27f17f28c23b050cd748365b39744aff2cf939ec87abbec27a5faf84d461e5d0.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80160b00.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x2405001D)
MUSASHI_NATIVE_MIPS_WORD(0x0C0582CD)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147078();
void func_80160B34();
void func_80160B00(void *p) {
    func_80147078(p, 29);
    func_80160B34(p);
}
#endif
