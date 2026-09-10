/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013D164,8013D178).
 * Offset 0x1500C at overlay base 80128158. SHA256(span)=2f8632a34c9d3154dcc3eb365b9e994105a08f06494dae3e92889d0c42d80950.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_801841C8->D_801A44F0.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801A)
MUSASHI_NATIVE_MIPS_WORD(0xAC2244F0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801A44F0;

void func_8013D164(void) {
    D_801A44F0 = 1;
}

#endif
