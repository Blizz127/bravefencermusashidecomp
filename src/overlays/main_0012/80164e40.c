/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 a, b, c, d; } G;
extern G D_80184358;
s32 func_80164E40(void) {
    if (D_80184358.a) {
        D_80184358.a = D_80184358.a - 0x10;
    }
    if (D_80184358.b) {
        D_80184358.b = D_80184358.b - 0x10;
    }
    if (D_80184358.c) {
        D_80184358.c = D_80184358.c - 0x10;
    }
    return *(s32 *)&D_80184358 == 0;
}
