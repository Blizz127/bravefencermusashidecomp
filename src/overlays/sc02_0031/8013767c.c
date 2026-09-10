/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013767C,801376C8).
 * Offset 0xF524 at overlay base 80128158. SHA256(span)=9596955eae32d7e2fcb33ac6455e89ca0c32d51becb5e238cb18a488f52622db.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013767c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04E66A)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x12000004)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C04DDED)
MUSASHI_NATIVE_MIPS_WORD(0x02003021)
MUSASHI_NATIVE_MIPS_WORD(0x02001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_801377B4(s32, s32, s32);                       /* static */
s32 func_801399A8();                                /* static */

s32 func_8013767C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_801399A8();
    if (temp_v0 != 0) {
        func_801377B4(arg0, 0, temp_v0);
    }
    return temp_v0;
}
#endif
