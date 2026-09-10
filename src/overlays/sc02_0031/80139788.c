/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139788,801397B0).
 * Offset 0x11630 at overlay base 80128158. SHA256(span)=488d676af2d3cf75aad9144117303cbe4086ef4d23b872ec68f637174ceaa2a4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139788.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0064C7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA420752C)
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

void func_8001931C();                                  /* extern */
extern s16 D_8012752C;

void func_80139788(void) {
    func_8001931C();
    D_8012752C = 0;
}
#endif
