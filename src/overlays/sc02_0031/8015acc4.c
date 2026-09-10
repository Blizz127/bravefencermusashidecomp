/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015ACC4,8015AD08).
 * Offset 0x32B6C at overlay base 80128158. SHA256(span)=df1da00e14740060ab3b636dc67b868c5b5f27927cfde04e1b32384bc59b8a7c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015acc4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x24050002)
MUSASHI_NATIVE_MIPS_WORD(0x0C053B4A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C053E81)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C056B6C)
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
void func_8014ED28();
void func_8014FA04();
void func_8015ADB0();
void func_8015ACC4(void *p) {
    func_80147078(p, 2);
    func_8014ED28(p);
    func_8014FA04(p);
    func_8015ADB0(p);
}
#endif
