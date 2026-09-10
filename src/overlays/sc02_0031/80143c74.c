/* SC02.CD FILE_031 / ov_SC02_031 retail span [80143C74,80143C98).
 * Offset 0x1BB1C at overlay base 80128158. SHA256(span)=d2af54763a1a1a97bfb6c210927ca9b5cec309a1069102d9c14da906a054a8a6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80143c74.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B196)
MUSASHI_NATIVE_MIPS_WORD(0x24040205)
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
void func_8012C658();
void func_80143C74(void *p, void *q) { func_8012C658(0x205, q, p); }
#endif
