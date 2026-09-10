/* Exact retail word export for [800301A4,800301C8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x9042AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA42046CC)
MUSASHI_NATIVE_MIPS_WORD(0x304200FD)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA022AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_8006AEF4;
extern s16 D_800A46CC;

s32 func_800301A4(void) {
    D_800A46CC = 0;
    D_8006AEF4 &= 0xFD;
    return 1;
}
#endif
