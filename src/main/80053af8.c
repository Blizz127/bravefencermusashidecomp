/* Exact retail word export for [80053AF8,80053B20); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00042103)
MUSASHI_NATIVE_MIPS_WORD(0x00052903)
MUSASHI_NATIVE_MIPS_WORD(0x0C01247F)
MUSASHI_NATIVE_MIPS_WORD(0x00063103)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800491FC(s32, s32, s32);                     /* static */

void func_80053AF8(s32 arg0, s32 arg1, s32 arg2) {
    func_800491FC(arg0 >> 4, arg1 >> 4, arg2 >> 4);
}
#endif
