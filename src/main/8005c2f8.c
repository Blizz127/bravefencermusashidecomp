/* Main-exec range [8005C2F8,8005C324) from the SLUS executable.
 * SHA256(span)=ce016d0ab2cc9930cb589c33f0e36cd7c3f726c5b638add09880391cff8c03e6.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C0173CA)
MUSASHI_NATIVE_MIPS_WORD(0x24060001)
MUSASHI_NATIVE_MIPS_WORD(0x93A20010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x3042007F)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_8005CF28(s32, u8 *, s32);                        /* static */

s32 func_8005C2F8(void) {
    u8 sp10;

    func_8005CF28(0, &sp10, 1);
    return sp10 & 0x7F;
}
#endif
