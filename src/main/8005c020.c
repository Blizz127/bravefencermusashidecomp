/* Exact retail word export for [8005C020,8005C054); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c0108e7)
MUSASHI_NATIVE_MIPS_WORD(0x2404ffff)
MUSASHI_NATIVE_MIPS_WORD(0x244200f0)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac2228a0)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0xac2028a4)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800728A0;
extern s32 D_800728A4;

s32 func_8004239C();                               /* static */

void func_8005C020(void) {
    D_800728A0 = func_8004239C(-1) + 0xF0;
    D_800728A4 = 0;
}
#endif
