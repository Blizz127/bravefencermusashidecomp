/* SC02 resident retail span [8013D13C,8013D164). Offset 0x14FE4 at base 80128158.
 * SHA256(span)=5a8aaafcc3e30a3336e625738522d45f62a5f8bb713b76d130dbc7b2a8391b6a.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_801841BC->D_801B6374.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F66C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C426374)
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

extern s32 D_801B6374;
void func_8013D9B0();                                  /* static */

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801B6374;
}

#endif
