/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_8005CF28(s32, u8 *, s32);                        /* static */

s32 func_8005C2F8(void) {
    u8 sp10;

    func_8005CF28(0, &sp10, 1);
    return sp10 & 0x7F;
}
