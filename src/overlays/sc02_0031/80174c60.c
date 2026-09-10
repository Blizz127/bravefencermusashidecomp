/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174C60,80174C80).
 * Offset 0x4CB08 at overlay base 80128158. SHA256(span)=dd39b8719308e906ae62013bbd0c5f69802cc117956aa6ff5938ff8c0d18ab72.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174c60.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D32C)
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
void func_80174CB0();
void func_80174C60(void *p) {
    func_80174CB0(p, 0);
}
#endif
