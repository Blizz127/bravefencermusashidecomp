#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80015118(u16 *arg0) {
    if ((u32) (*arg0 - 0x15) < 0xD7U) {
        *arg0 = 0x80;
    }
}
