/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad_0[16];
    s32 f10;
    s32 f14;
    s32 f18;
} T;
void func_80146D80(T *p) {
    p->f18 = 0;
    p->f14 = 0;
    p->f10 = 0;
}
