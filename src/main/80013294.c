/* Main-exec range [80013294,800132BC) from the SLUS executable.
 * SHA256(span)=cff54305588bdf00b31a4655d16c87d33482d1f85b391bcc16df83b3632767f5.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C004CAF)
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

s32 func_800132BC();                                /* static */
void func_80047D3C(s32);                               /* static */

void func_80013294(void) {
    func_80047D3C(func_800132BC());
}
#endif
