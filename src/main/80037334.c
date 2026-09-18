/* Exact retail word export for [80037334,80037358); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xA0206251)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0x0441FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_80076251[];

/* Identical twin of func_80037004: same table, same top-down
 * zeroing. See there for the codegen notes. */
void func_80037334(void) {
    s32 i = 0x40;

    do {
        D_80076251[i] = 0;
        i -= 0x10;
    } while (i >= 0);
}
#endif
