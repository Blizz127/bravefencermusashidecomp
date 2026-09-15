/* Main-exec range [8001B23C,8001B26C) from the SLUS executable.
 * SHA256(span)=bbb62775814a0011918e338fe5264e6822f4ed3d5d2d5d2bab51d26f6d6001ce.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xAC246D34)
MUSASHI_NATIVE_MIPS_WORD(0x0C006C9B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x8C426D10)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8001B26C();                                  /* static */
extern s32 D_800C6D10;
extern s32 D_800C6D34;

s32 func_8001B23C(s32 arg0) {
    D_800C6D34 = arg0;
    func_8001B26C();
    return D_800C6D10;
}
#endif
