/* Exact retail word export for [8001A0FC,8001A114); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0xAC20E6F4)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0xAC20E70C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800AE6F4;
extern s32 D_800AE70C;

void func_8001A0FC(void) {
    D_800AE6F4 = 0;
    D_800AE70C = 0;
}
#endif
