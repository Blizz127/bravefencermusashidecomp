/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165840,80165874).
 * Offset 0x3D6E8 at overlay base 80128158. SHA256(span)=adc475373e005e248fee63021ecbcaf7a0baf3020d0f9a4cbdc3b74d517f88bd.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80165840.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EC3)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xA0208EC3)
MUSASHI_NATIVE_MIPS_WORD(0x0C05961D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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

void func_80165874();                                  /* static */
extern u8 D_80078EC3;

void func_80165840(void) {
    if (D_80078EC3 != 0) {
        D_80078EC3 = 0;
        func_80165874();
    }
}
#endif
