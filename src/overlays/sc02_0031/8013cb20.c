/* SC02 resident retail span [8013CB20,8013CB5C). Offset 0x149C8 at base 80128158.
 * SHA256(span)=b664efb4f5b8642970e7a6a9a549aa0367bb988d03d15ce4ae7771d820a308da.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_801841BC->D_801B6374; D_801841C0->D_801B6378; D_801841E8->D_801B63A0; D_801841EC->D_801B63A4.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C426378)
MUSASHI_NATIVE_MIPS_WORD(0x3C04801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C846374)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC236378)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC206374)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC2263A0)
MUSASHI_NATIVE_MIPS_WORD(0x3C01801B)
MUSASHI_NATIVE_MIPS_WORD(0xAC2463A4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801B6374;
extern s32 D_801B6378;
extern s32 D_801B63A0;
extern s32 D_801B63A4;

void func_8013CB20(void) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = D_801B6378;
    temp_a0 = D_801B6374;
    D_801B6378 = 1;
    D_801B6374 = 0;
    D_801B63A0 = temp_v0;
    D_801B63A4 = temp_a0;
}

#endif
