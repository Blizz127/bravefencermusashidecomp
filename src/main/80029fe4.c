/* Main-exec range [80029FE4,8002A04C) from the SLUS executable.
 * SHA256(span)=3009aff5cba9d65c384780bb2c9fd192ac4593c1c0eea1208003e3c832d04041.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A89B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A92E)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A9CA)
MUSASHI_NATIVE_MIPS_WORD(0x00409021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA66)
MUSASHI_NATIVE_MIPS_WORD(0x00408821)
MUSASHI_NATIVE_MIPS_WORD(0x02128021)
MUSASHI_NATIVE_MIPS_WORD(0x02118021)
MUSASHI_NATIVE_MIPS_WORD(0x02021021)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420003)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8002A26C();                                /* static */
s32 func_8002A4B8();                                /* static */
s32 func_8002A728();                                /* static */
s32 func_8002A998();                                /* static */

s32 func_80029FE4(void) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = func_8002A26C();
    temp_s2 = func_8002A4B8();
    temp_s1 = func_8002A728();
    return (s32) (temp_s0 + temp_s2 + temp_s1 + func_8002A998()) / 4;
}
#endif
