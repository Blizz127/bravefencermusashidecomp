/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F4C4,8016F4F4).
 * Offset 0x4736C at overlay base 80128158. SHA256(span)=eb9adc8f8be204dd3f444f027bb592ae12dfcc7cb36c38a0a4206b0a096a4847.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f4c4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BC39)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0595DC)
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

void func_80165770(s32);                               /* static */
void func_8016F0E4();                                  /* static */

void func_8016F4C4(s32 arg0) {
    func_8016F0E4();
    func_80165770(arg0);
}
#endif
