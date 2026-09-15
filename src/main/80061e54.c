/* Main-exec range [80061E54,80061E90) from the SLUS executable.
 * SHA256(span)=390bfc120f1aebe4f54acf05d820be7fed577ca93473fc63c42243fba3fcf901.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428C70)
MUSASHI_NATIVE_MIPS_WORD(0x3C048008)
MUSASHI_NATIVE_MIPS_WORD(0x8C848C6C)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x8C638C74)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x00031880)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428C78)
MUSASHI_NATIVE_MIPS_WORD(0x00832021)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00821021)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078C6C;
extern s32 D_80078C70;
extern s32 D_80078C74;
extern s32 D_80078C78;

s32 func_80061E54(void) {
    return D_80078C6C + (D_80078C70 * 2) + (D_80078C74 * 4) + (D_80078C78 * 8);
}
#endif
