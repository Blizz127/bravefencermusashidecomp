/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015A1FC,8015A230).
 * Offset 0x320A4 at overlay base 80128158. SHA256(span)=f4eeba17a88ef0a8b05962edfd4e1365ba3b2061c82a9d7a0831bfa74fdea02f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015a1fc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x24050001)
MUSASHI_NATIVE_MIPS_WORD(0x0C0568B6)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147078();
void func_8015A2D8();
void func_8015A1FC(void *p) {
    func_80147078(p, 1);
    func_8015A2D8(p);
}
#endif
