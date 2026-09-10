/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801757A0();
extern s16 D_800B9A02;
typedef struct { u8 pad[1]; u8 v; } T;
void func_80175624(T *p) {
    func_801757A0(D_800B9A02);
    p->v += 1;
}
