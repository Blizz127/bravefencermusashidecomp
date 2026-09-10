/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171238,80171260).
 * Offset 0x490E0 at overlay base 80128158. SHA256(span)=1a3e70f34f990123074549ef25454c10e2d92a621c86ae9696307eae206f546f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171238.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x8C84F738)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C62B)
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

void func_801718AC(s32);                               /* static */
extern s32 D_8011F738;

void func_80171238(void) {
    func_801718AC(D_8011F738);
}
#endif
