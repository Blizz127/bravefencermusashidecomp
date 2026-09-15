/* Main-exec range [80058EC4,80058EE4) from the SLUS executable.
 * SHA256(span)=a5d701f978e868989dd5b60a694c792b5272019e0f68bfee6255c47c3aa7bc73.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C035555)
MUSASHI_NATIVE_MIPS_WORD(0x34635555)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x24020048)
MUSASHI_NATIVE_MIPS_WORD(0xA0820007)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC830014)
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
    u8 rest[12];
    u32 tag;
} P;
void func_80058EC4(P *p) {
    p->code = 5;
    p->code2 = 72;
    p->tag = 0x55555555u;
}
#endif
