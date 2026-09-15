/* Main-exec range [80036F98,80036FB0) from the SLUS executable.
 * SHA256(span)=46dd9ea66da7b76736e6b5a4d43ebf2ac4a5afc6b57fd9841ec56f123fecbc1b.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC208F10)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC20AEE8)
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

void func_80036F98(void) {
    D_80078F10 = 0;
    D_8006AEE8 = 0;
}
#endif
