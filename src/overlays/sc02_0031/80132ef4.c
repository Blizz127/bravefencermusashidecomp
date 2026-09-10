/* SC02.CD FILE_031 / ov_SC02_031 retail span [80132EF4,80132F40).
 * Offset 0xAD9C at overlay base 80128158. SHA256(span)=fb36d751c936b2f15f652610cce54ab0d3280c8f823cabc98705f888381a80d1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80132ef4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0x30A4FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A44F)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x12000003)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A4D4)
MUSASHI_NATIVE_MIPS_WORD(0x02202821)
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

s32 func_8012913C(s32);                             /* static */
void func_80129350(s32, s32);                          /* static */

s32 func_80132EF4(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_8012913C(arg1 & 0xFFFF);
    if (temp_v0 != 0) {
        func_80129350(temp_v0, arg0);
    }
    return temp_v0;
}
#endif
