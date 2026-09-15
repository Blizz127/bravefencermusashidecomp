/* Main-exec range [80029AAC,80029AF4) from the SLUS executable.
 * SHA256(span)=dadd0e5ca9751af67326eabb7b725917612751c2f0005e449f43a5752cc51418.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A8AC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C0451EB)
MUSASHI_NATIVE_MIPS_WORD(0x3484851F)
MUSASHI_NATIVE_MIPS_WORD(0x00021880)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x00031100)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x00440018)
MUSASHI_NATIVE_MIPS_WORD(0x000217C3)
MUSASHI_NATIVE_MIPS_WORD(0x00002810)
MUSASHI_NATIVE_MIPS_WORD(0x00051943)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00621023)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8002A2B0();                                /* static */

s32 func_80029AAC(void) {
    return (func_8002A2B0() * 0x4B) / 100;
}
#endif
