/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 t; s16 a; s16 b; s32 ptr; u8 c; u8 d; } T;
void func_80015424(T *p, s32 a1, s16 a2, s16 a3, u8 a4, u8 a5) {
    p->t = 2;
    p->a = a2;
    p->b = a3;
    p->ptr = a1;
    p->c = a4;
    p->d = a5;
}
