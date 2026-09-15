/* Main-exec range [800166E8,80016714) from the SLUS executable.
 * SHA256(span)=f160358835eeb22464bb5078c81cb043767770af9352c777824df85bea4cc7cc.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A00006)
MUSASHI_NATIVE_MIPS_WORD(0x24A2FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA0800000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1443FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_800166E8(char *arg0, int arg1) {
    while (arg1--) {
        *arg0++ = 0;
    }
}
#endif
