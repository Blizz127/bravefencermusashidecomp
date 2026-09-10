/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E814,8013E83C).
 * Offset 0x166BC at overlay base 80128158. SHA256(span)=bb012f763e07bf5281ee169375c2417a10b44a78c6374f4ac54c644cd6aa62c9.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e814.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C034928)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F9AB)
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

void func_800D24A0();                                 /* extern */
void func_8013E6AC();                                  /* static */

void func_8013E814(void) {
    func_800D24A0(0);
    func_8013E6AC();
}
#endif
