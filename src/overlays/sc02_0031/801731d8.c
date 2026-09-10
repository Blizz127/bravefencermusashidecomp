/* SC02.CD FILE_031 / ov_SC02_031 retail span [801731D8,80173220).
 * Offset 0x4B080 at overlay base 80128158. SHA256(span)=6fbcf76a0c1c81b0b4971aab73d7e86400365b760adabdb34bcc407036ecb96a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801731d8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1B)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800D)
MUSASHI_NATIVE_MIPS_WORD(0x24A55AA0)
MUSASHI_NATIVE_MIPS_WORD(0x0C05509D)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C687)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05CC88)
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
void func_80154274(s32, void *);                          /* static */
void func_80171A1C(s32);                               /* static */
void func_80173220(s32);                               /* static */
extern s32 *D_800D5AA0;

void func_801731D8(s32 arg0) {
    func_8014706C();
    func_80154274(arg0, &D_800D5AA0);
    func_80171A1C(arg0);
    func_80173220(arg0);
}
#endif
