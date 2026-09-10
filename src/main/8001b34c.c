#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xac20654c)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac2047f8)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800a)
MUSASHI_NATIVE_MIPS_WORD(0xac202b70)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0xac20a0fc)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800747F8;
extern s32 D_800A2B70;
extern s32 D_800A654C;
extern s32 D_800BA0FC;

void func_8001B34C(void) {
    D_800A654C = 0;
    D_800747F8 = 0;
    D_800A2B70 = 0;
    D_800BA0FC = 0;
}
