/* Main-exec range [80058F04,80058F24) from the SLUS executable.
 * SHA256(span)=8ab8606f4152e8b95265d654b14242300d208cae33739f27aa02a8f46d5f497f.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C035555)
MUSASHI_NATIVE_MIPS_WORD(0x34635555)
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x2402004C)
MUSASHI_NATIVE_MIPS_WORD(0xA0820007)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC830018)
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
typedef struct {
    u8 r,g,b,code;
    u8 r2,g2,b2,code2;
    u8 rest[16];
    u32 tag;
} P;
void func_80058F04(P *p) {
    p->code = 6;
    p->code2 = 76;
    p->tag = 0x55555555u;
}
#endif
