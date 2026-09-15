/* Main-exec range [80036D24,80036D58) from the SLUS executable.
 * SHA256(span)=d8fdd1214ca235c52358f116e909606fa2e2ad82862095e42caa8f88f95e0342.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42AEE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC208F10)
MUSASHI_NATIVE_MIPS_WORD(0x28420002)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC20AEE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA0204F1A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern s8 D_800A4F1A;

void func_80036D24(void) {
    D_80078F10 = 0;
    if (D_8006AEE8 < 2) {
        D_8006AEE8 = 0;
        D_800A4F1A = 0;
    }
}
#endif
