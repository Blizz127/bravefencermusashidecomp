/* SC02.CD FILE_031 / ov_SC02_031 retail span [801289F0,80128A28).
 * Offset 0x898 at overlay base 80128158. SHA256(span)=d594734a780b5569437ad454c3c035d61905a6ce074e761a7dfa9595843ee902.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_80182D1C->D_801A3234.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3C07801A)
MUSASHI_NATIVE_MIPS_WORD(0x8CE73234)
MUSASHI_NATIVE_MIPS_WORD(0x3C06800B)
MUSASHI_NATIVE_MIPS_WORD(0x24C6ECB8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C006AEF)
MUSASHI_NATIVE_MIPS_WORD(0xAFA00010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8001ABBC(s32, s32, void *, s32, s32);               /* extern */
extern s32 D_801A3234;
extern s32 *D_800AECB8;

void func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_801A3234, 0);
}

#endif
