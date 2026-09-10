/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015BF7C,8015BFB0).
 * Offset 0x33E24 at overlay base 80128158. SHA256(span)=943600a6c6433bd03b21174ba710128a2c7455312d60fb0d7660f9b44668662b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015bf7c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x24050004)
MUSASHI_NATIVE_MIPS_WORD(0x0C056FFD)
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
void func_8015BFF4();
void func_8015BF7C(void *p) {
    func_80147078(p, 4);
    func_8015BFF4(p);
}
#endif
