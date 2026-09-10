/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x308500ff)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a468)
MUSASHI_NATIVE_MIPS_WORD(0x2404002d)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

void func_800291A0(s32, s32);                            /* static */

void func_80029020(s32 arg0) {
    func_800291A0(0x2D, arg0 & 0xFF);
}
