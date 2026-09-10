/* SC02.CD FILE_031 / ov_SC02_031 retail span [801730B4,801730FC).
 * Offset 0x4AF5C at overlay base 80128158. SHA256(span)=dd9333707b89726e92e1d8bf917c17c3be5441f40d5e8cec0a8a1bc1da71185c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801730b4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1B)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x8CA57508)
MUSASHI_NATIVE_MIPS_WORD(0x0C0550A9)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C687)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05CC3F)
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

void func_8014706C();                                  /* static */
void func_801542A4(s32, s32);                          /* static */
void func_80171A1C(s32);                               /* static */
void func_801730FC(s32);                               /* static */
extern s32 D_80127508;

void func_801730B4(s32 arg0) {
    func_8014706C();
    func_801542A4(arg0, D_80127508);
    func_80171A1C(arg0);
    func_801730FC(arg0);
}
#endif
