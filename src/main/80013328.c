/* Main-exec range [80013328,80013350) from the SLUS executable.
 * SHA256(span)=a96c187b69e21a1c657c6f973c55f08ed39c849731f296080c2d71669558b5be.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C004CD4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C011F4F)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
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

s32 func_80013350();                                /* static */
void func_80047D3C(s32);                               /* static */

void func_80013328(void) {
    func_80047D3C(func_80013350());
}
#endif
