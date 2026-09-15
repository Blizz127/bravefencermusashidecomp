/* Main-exec range [80029AF4,80029B4C) from the SLUS executable.
 * SHA256(span)=161e62f091de7bef562cd286ad5af0c69a2edc98b872383e7fa95d358e4aeeb1.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A78C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A735)
MUSASHI_NATIVE_MIPS_WORD(0x24040028)
MUSASHI_NATIVE_MIPS_WORD(0x244200C8)
MUSASHI_NATIVE_MIPS_WORD(0x02020018)
MUSASHI_NATIVE_MIPS_WORD(0x00008012)
MUSASHI_NATIVE_MIPS_WORD(0x3C0251EB)
MUSASHI_NATIVE_MIPS_WORD(0x3442851F)
MUSASHI_NATIVE_MIPS_WORD(0x02020018)
MUSASHI_NATIVE_MIPS_WORD(0x001087C3)
MUSASHI_NATIVE_MIPS_WORD(0x00001810)
MUSASHI_NATIVE_MIPS_WORD(0x00031143)
MUSASHI_NATIVE_MIPS_WORD(0x00501023)
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

s32 func_80029CD4();                               /* static */
s32 func_80029E30();                                /* static */

s32 func_80029AF4(void) {
    s32 temp_s0;

    temp_s0 = func_80029E30();
    return (temp_s0 * (func_80029CD4(0x28) + 0xC8)) / 100;
}
#endif
