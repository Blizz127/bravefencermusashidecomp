/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128178,80128198).
 * Offset 0x20 at overlay base 80128158. SHA256(span)=4a5ccfebeb75aa8509d2e24a116b4c377e1591c955e77133fb1fa2e2f13218cd.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80128178.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A179)
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

void func_801285E4();                                  /* static */

void func_80128178(void) {
    func_801285E4();
}
#endif
