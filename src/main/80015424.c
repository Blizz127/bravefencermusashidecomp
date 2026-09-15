/* Main-exec range [80015424,8001544C) from the SLUS executable.
 * SHA256(span)=454b1fddaab4358cccacab3854d837bbef647c51eb237af900d04196eccb12c0.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x93A30010)
MUSASHI_NATIVE_MIPS_WORD(0x93A80014)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0xA4820000)
MUSASHI_NATIVE_MIPS_WORD(0xA4860002)
MUSASHI_NATIVE_MIPS_WORD(0xA4870004)
MUSASHI_NATIVE_MIPS_WORD(0xAC850008)
MUSASHI_NATIVE_MIPS_WORD(0xA083000C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA088000D)
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
typedef struct { s16 t; s16 a; s16 b; s32 ptr; u8 c; u8 d; } T;
void func_80015424(T *p, s32 a1, s16 a2, s16 a3, u8 a4, u8 a5) {
    p->t = 2;
    p->a = a2;
    p->b = a3;
    p->ptr = a1;
    p->c = a4;
    p->d = a5;
}
#endif
