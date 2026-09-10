/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015DE24,8015DE58).
 * Offset 0x35CCC at overlay base 80128158. SHA256(span)=65a7bd22f0c2238f6b7921a77f728629f028edd837daa0b0168b6a9c8885f0d0.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015de24.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x2405000F)
MUSASHI_NATIVE_MIPS_WORD(0x0C057796)
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
void func_8015DE58();
void func_8015DE24(void *p) {
    func_80147078(p, 15);
    func_8015DE58(p);
}
#endif
