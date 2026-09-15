/* Main-exec range [800434DC,800434F4) from the SLUS executable.
 * SHA256(span)=9d8daa8f9c0f37e914d696c5740fdccf00410789021f47ff02b961c1e836c55e.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42CC90)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC24CC90)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006CC90;

s32 func_800434DC(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8006CC90;
    D_8006CC90 = arg0;
    return temp_v0;
}
#endif
