/* Main-exec range [80061E18,80061E54) from the SLUS executable.
 * SHA256(span)=521486e91979a9daee5e169944e05abc9bb1655132d161b51aeb208fe2ebb63c.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428C60)
MUSASHI_NATIVE_MIPS_WORD(0x3C048008)
MUSASHI_NATIVE_MIPS_WORD(0x8C848C5C)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x8C638C64)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x00031880)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428C68)
MUSASHI_NATIVE_MIPS_WORD(0x00832021)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00821021)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078C5C;
extern s32 D_80078C60;
extern s32 D_80078C64;
extern s32 D_80078C68;

s32 func_80061E18(void) {
    return D_80078C5C + (D_80078C60 * 2) + (D_80078C64 * 4) + (D_80078C68 * 8);
}
#endif
