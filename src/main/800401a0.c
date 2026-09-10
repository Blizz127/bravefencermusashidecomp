#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006B580;

void func_800401A0(s32 arg0) {
    if (arg0 == 1) {
        D_8006B580 = 0;
        return;
    }
    D_8006B580 = 1;
}
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
/* Retail word export for [800401A0,800401CC); EXE-verified. */
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x14820005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac20b580)
MUSASHI_NATIVE_MIPS_WORD(0x08010071)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac22b580)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
