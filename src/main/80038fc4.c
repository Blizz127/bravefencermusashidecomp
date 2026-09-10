/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80038FC4(u8 **p) {
    s32 acc = 0;
    u8 b;
    do {
        b = **p;
        *p = *p + 1;
        acc = acc + (b & 0x7F);
        if (b & 0x80) {
            acc = acc << 7;
        }
    } while (b & 0x80);
    return acc;
}
