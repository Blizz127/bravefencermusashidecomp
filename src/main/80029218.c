/* Main-exec range [80029218,80029240) from the SLUS executable.
 * SHA256(span)=15bb6fe256bd269fdbe493fe25e1a0411c24465e936f2b3880c739c4eb5b6e17.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800B)
MUSASHI_NATIVE_MIPS_WORD(0x2484E6A8)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x2405003C)
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
extern s32 *D_800AE6A8;

void func_80029218(void) {
    func_80016714(&D_800AE6A8, 0x3C);
}
#endif
