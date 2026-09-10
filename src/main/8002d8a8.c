#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020006)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA42260EC)
MUSASHI_NATIVE_MIPS_WORD(0x3C028003)
MUSASHI_NATIVE_MIPS_WORD(0x2442FA3C)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xAC224F24)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA42060E8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020010)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8002FA3C();
extern s16 D_800760EC;
extern void (*D_800A4F24)();
extern s16 D_800760E8;
s32 func_8002D8A8(void) {
    D_800760EC = 6;
    D_800A4F24 = func_8002FA3C;
    D_800760E8 = 0;
    return 0x10;
}
#endif
