/* Main-exec range [80028F10,80028F34) from the SLUS executable.
 * SHA256(span)=b8c7704f212aaf325a8ae310ef69d8d24c0555921c3b8b182f7989c9c1903ba2.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x308500FF)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A449)
MUSASHI_NATIVE_MIPS_WORD(0x24040011)
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

void func_80029124(s32, s32);                            /* static */

void func_80028F10(s32 arg0) {
    func_80029124(0x11, arg0 & 0xFF);
}
#endif
