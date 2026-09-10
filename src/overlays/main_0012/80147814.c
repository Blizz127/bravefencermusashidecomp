/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x34]; s32 f; } T;
void func_80147814(T *p, s32 d) {
    p->f += d;
    if (d < 0 && p->f < -0x1F0000)
        p->f = -0x1F0000;
    else if (d > 0 && p->f > 0x1F0000)
        p->f = 0x1F0000;
}
