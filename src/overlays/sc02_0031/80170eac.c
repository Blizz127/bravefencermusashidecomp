/* SC02.CD FILE_031 / ov_SC02_031 retail span [80170EAC,80170EFC).
 * Offset 0x48D54 at overlay base 80128158. SHA256(span)=a1cbfbb658223e90c6ed5b38fa84f857ce39f4080a62c1cac79cf9474c1d05cf.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80170eac.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x9084F738)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0343E3)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x8C84F73C)
MUSASHI_NATIVE_MIPS_WORD(0x0805C3B9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x8C84F740)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C62B)
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

s32 func_800D0F8C(u8);                              /* extern */
void func_801718AC(s32);                               /* static */
extern u8 D_8011F738;
extern s32 D_8011F73C;
extern s32 D_8011F740;

void func_80170EAC(void) {
    s32 var_a0;

    if (func_800D0F8C(D_8011F738) != 0) {
        var_a0 = D_8011F73C;
    } else {
        var_a0 = D_8011F740;
    }
    func_801718AC(var_a0);
}
#endif
