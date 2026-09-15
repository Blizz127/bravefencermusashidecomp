/* Main-exec range [80038FC4,80038FFC) from the SLUS executable.
 * SHA256(span)=465019c005a5c44778e07ada7f40aa40dec4c3234b11d1315408b029eee885fc.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x90430000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0x3062007F)
MUSASHI_NATIVE_MIPS_WORD(0x30630080)
MUSASHI_NATIVE_MIPS_WORD(0x10600003)
MUSASHI_NATIVE_MIPS_WORD(0x00A22821)
MUSASHI_NATIVE_MIPS_WORD(0x0800E3F2)
MUSASHI_NATIVE_MIPS_WORD(0x000529C0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80038FC4(u8 **p) {
    s32 acc = 0;
    u8 b;
    do {
        b = **p;
        *p = *p + 1;
        acc = acc + (b & 0x7F);
        if (b & 0x80) {
            acc = acc << 7;
        }
    } while (b & 0x80);
    return acc;
}
#endif
