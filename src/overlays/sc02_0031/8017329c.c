/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017329C,801732C4).
 * Offset 0x4B144 at overlay base 80128158. SHA256(span)=7cf072b11c2c5860a46e8b58c236bee0dcffb886465a281f4e9484b519eb16a2.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017329c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C048017)
MUSASHI_NATIVE_MIPS_WORD(0x248432C4)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D1A1)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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
void func_80174684();
void func_801732C4();
void func_8017329C(void) {
    func_80174684(func_801732C4);
}
#endif
