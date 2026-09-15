/* Main-exec range [8001AA88,8001AA98) from the SLUS executable.
 * SHA256(span)=5a82bb4bb21dce36b9c8dc4bb0f3567d7947ea32acd6274dad4ef8fe5bc4a941.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0xAC24E708)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800AE708;

void func_8001AA88(s32 arg0) {
    D_800AE708 = arg0;
}
#endif
