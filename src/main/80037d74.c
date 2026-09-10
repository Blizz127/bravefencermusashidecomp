/* Exact retail word export for [80037D74,80037D98); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x9042AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xAC20A0F8)
MUSASHI_NATIVE_MIPS_WORD(0x304200FD)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA022AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_8006AEF4;
extern s32 D_800BA0F8;

void func_80037D74(void) {
    D_800BA0F8 = 0;
    D_8006AEF4 &= 0xFD;
}
#endif
