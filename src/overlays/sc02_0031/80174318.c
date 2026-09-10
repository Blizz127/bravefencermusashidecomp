/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174318,80174354).
 * Offset 0x4C1C0 at overlay base 80128158. SHA256(span)=f408df23b5b118b03191cdf3809de3f47b1fbea372ae69601de927e5795f0007.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174318.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C050915)
MUSASHI_NATIVE_MIPS_WORD(0x2404FF80)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C687)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D194)
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

void func_80142454();                                 /* static */
void func_80171A1C(s32);                               /* static */
void func_80174650(s32);                               /* static */

void func_80174318(s32 arg0) {
    func_80142454(-0x80);
    func_80171A1C(arg0);
    func_80174650(arg0);
}
#endif
