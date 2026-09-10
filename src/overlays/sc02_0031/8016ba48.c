/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016BA48,8016BA68).
 * Offset 0x438F0 at overlay base 80128158. SHA256(span)=d59cee3f0877d1af61a0218e763ea5891de21b8d69b477a5bba57964f57c98d1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016ba48.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05AE9A)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016BA68();
void func_8016BA48(void *p) {
    func_8016BA68(p, 0);
}
#endif
