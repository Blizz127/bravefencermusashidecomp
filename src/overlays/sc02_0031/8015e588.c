/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015E588,8015E5B0).
 * Offset 0x36430 at overlay base 80128158. SHA256(span)=950a2a13f8428efb3396fc786feca945b4ff7ccf7ffd494cc076fc49e1486763.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_80180CF4 here is D_8018157C (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C048018)
MUSASHI_NATIVE_MIPS_WORD(0x2484157C)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F271)
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
extern s32 D_8018157C;
void func_8013C9C4();
void func_8015E588(void) {
    func_8013C9C4(&D_8018157C);
}
#endif
