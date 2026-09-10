/* Exact retail word export for [8003D424,8003D434); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x8c42b0fc)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xac820000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006B0FC;

void func_8003D424(s32 *arg0) {
    *arg0 = D_8006B0FC;
}
#endif
