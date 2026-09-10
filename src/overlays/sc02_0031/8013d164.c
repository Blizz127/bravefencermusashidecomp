/* SC02 resident retail span [8013D164,8013D178). Offset 0x1500C at base 80128158.
 * SHA256(span)=6349d58e7da1a8bfa1907391e4dc3a2f2fba28d6db95c5fe16e2428f4657e86c.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_801841C8->D_801B6380.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC226380)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801B6380;

void func_8013D164(void) {
    D_801B6380 = 1;
}

#endif
