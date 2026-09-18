/* Exact retail word export for [8003834C,8003836C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000411C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xA4259ECA)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800B9ECA;

void func_8003834C(s32 arg0, s32 arg1) {
    *(u16 *)((u8 *)&D_800B9ECA + ((arg0 * 127) * 4)) = (u16)arg1;
}
#endif
