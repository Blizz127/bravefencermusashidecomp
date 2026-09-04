#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8001D150(s32 arg0, s32 arg1) {
    s32 *temp_a1;

    temp_a1 = (arg1 * 4) + arg0;
    *temp_a1 |= 0x01000000;
}
