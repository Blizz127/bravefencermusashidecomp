/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016FCCC,8016FD08).
 * Offset 0x47B74 at overlay base 80128158. SHA256(span)=8c5980139236178591e06b78151a84d016baaa479d6cdc3ab7b6ae2237689774.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016fccc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C669)
MUSASHI_NATIVE_MIPS_WORD(0x24050001)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C664)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BF42)
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
void func_801719A4();
void func_80171990();
void func_8016FD08();
void func_8016FCCC(void *p) {
    func_801719A4(p, 1);
    func_80171990(p);
    func_8016FD08(p);
}
#endif
