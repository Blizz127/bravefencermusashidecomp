/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174188,801741A8).
 * Offset 0x4C030 at overlay base 80128158. SHA256(span)=0aaa6bddafa1696aa62c3c92ef1518e1399f5859695258245ff9b8c85b734488.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174188.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C052F3B)
MUSASHI_NATIVE_MIPS_WORD(0x24050019)
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
void func_8014BCEC();
void func_80174188(void *p) {
    func_8014BCEC(p, 25);
}
#endif
