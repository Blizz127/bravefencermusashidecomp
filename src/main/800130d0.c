/* Main-exec range [800130D0,8001311C) from the SLUS executable.
 * SHA256(span)=fa9c5ce6a7e22581a31b3dcd1ef6b081040f8426ed3c4f90ae7c3dc837eb873f.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x00102400)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x00042403)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C004C47)
MUSASHI_NATIVE_MIPS_WORD(0x00063403)
MUSASHI_NATIVE_MIPS_WORD(0x02028021)
MUSASHI_NATIVE_MIPS_WORD(0x00108400)
MUSASHI_NATIVE_MIPS_WORD(0x00101403)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8001311C(s16, s16, s16);                   /* static */

s16 func_800130D0(s16 arg0, s16 arg1, s16 arg2) {
    return (s16) (arg0 + func_8001311C(arg0, arg1, arg2));
}
#endif
