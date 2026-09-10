/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015BDD0,8015BE04).
 * Offset 0x33C78 at overlay base 80128158. SHA256(span)=6a265b17862a26e83ea45f43ef0643832d23a4b680d2a731a87493e61499927a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015bdd0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C1E)
MUSASHI_NATIVE_MIPS_WORD(0x24050003)
MUSASHI_NATIVE_MIPS_WORD(0x0C056FA5)
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
void func_8015BE94();
void func_8015BDD0(void *p) {
    func_80147078(p, 3);
    func_8015BE94(p);
}
#endif
