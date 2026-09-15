/* Main-exec range [80029094,800290BC) from the SLUS executable.
 * SHA256(span)=b3a78cf21a98fb8af2cb9f8c412f864969da8f17efd46b8100ab6f5d8b0515f0.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800C)
MUSASHI_NATIVE_MIPS_WORD(0x2484A2B8)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050060)
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

void func_80016714(void *, s32);                            /* static */
extern s32 *D_800BA2B8;

void func_80029094(void) {
    func_80016714(&D_800BA2B8, 0x60);
}
#endif
