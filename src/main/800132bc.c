/* Main-exec range [800132BC,80013328) from the SLUS executable.
 * SHA256(span)=f10c0baebdad460ec8dbf54574fbb7d4b374687f2afc3bf80faae71953f7a70c.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x84A30002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20014)
MUSASHI_NATIVE_MIPS_WORD(0x84820004)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x27A50020)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x0C0124C9)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20020)
MUSASHI_NATIVE_MIPS_WORD(0x8FA30024)
MUSASHI_NATIVE_MIPS_WORD(0x8FA40028)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
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
typedef struct { s16 x, y, z; } SVEC;
typedef struct { s32 x, y, z; } VEC;
void func_80049324();
s32 func_800132BC(SVEC *a, SVEC *b) {
    VEC d;
    VEC out;
    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    func_80049324(&d, &out);
    return out.x + out.y + out.z;
}
#endif
