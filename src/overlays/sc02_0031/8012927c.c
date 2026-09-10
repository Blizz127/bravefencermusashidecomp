/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012927C,801292C8).
 * Offset 0x1124 at overlay base 80128158. SHA256(span)=5dfa851c421f6574efc831adb85001c11505c0846129e38ac19302df45b26054.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012927c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x3C118012)
MUSASHI_NATIVE_MIPS_WORD(0x2631DB30)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00008021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A4B2)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x26100001)
MUSASHI_NATIVE_MIPS_WORD(0x2A020080)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x26310038)
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

void func_801292C8(void *);                               /* static */
extern s32 *D_8011DB30;

void func_8012927C(void) {
    void *var_s1;
    s32 var_s0;

    var_s1 = &D_8011DB30;
    var_s0 = 0;
    do {
        func_801292C8(var_s1);
        var_s0 += 1;
        var_s1 += 0x38;
    } while (var_s0 < 0x80);
}
#endif
