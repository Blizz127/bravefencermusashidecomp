/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013B7F4,8013B83C).
 * Offset 0x1369C at overlay base 80128158. SHA256(span)=317dbda6b8806d4c45946bb232e7f9e7d9dedd1fc56229f0da3a60a32acb4241.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_80185C74->D_801A58DC.
 * Oracle MATCH re-earned on this file; Not MAIN10.
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
MUSASHI_NATIVE_MIPS_WORD(0x3C06801A)
MUSASHI_NATIVE_MIPS_WORD(0x8CC658DC)
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

extern s32 D_801A58DC;
void func_8013B83C(s32, s32, s32);                     /* static */

void func_8013B7F4(s32 arg0, s32 arg1) {
    func_8013B83C(arg0, arg1, D_801A58DC);
}

#endif
