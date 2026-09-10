/* SC02 resident retail span [8013B7F4,8013B83C). Offset 0x1369C at base 80128158.
 * SHA256(span)=016908d764b8c30e2e810909a3f262c781c3ac810aed950edff6de5442f14784.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_80185C74->D_801B7B04.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0xAFC40018)
MUSASHI_NATIVE_MIPS_WORD(0xAFC5001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FC40018)
MUSASHI_NATIVE_MIPS_WORD(0x8FC5001C)
MUSASHI_NATIVE_MIPS_WORD(0x3C06801B)
MUSASHI_NATIVE_MIPS_WORD(0x8CC67B04)
MUSASHI_NATIVE_MIPS_WORD(0x0C04EE0F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801B7B04;
void func_8013B83C(s32, s32, s32);                     /* static */

void func_8013B7F4(s32 arg0, s32 arg1) {
    func_8013B83C(arg0, arg1, D_801B7B04);
}

#endif
