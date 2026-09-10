/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154218();
typedef struct { u8 pad[0xB0]; s32 *t; s32 b4; } T;
void func_801541D8(T *p, s32 a1) {
    if (p->b4 != p->t[a1]) {
        func_80154218(p, a1);
    }
}
