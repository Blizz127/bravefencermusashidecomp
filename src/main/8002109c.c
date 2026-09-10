/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800491FC();
typedef struct { s16 a, b, c, d; } V;
typedef struct { V *p; } T;
void func_8002109C(void *unused, T *t) {
    V *v = t->p;
    if (v->d == -2) {
        func_800491FC(v->a, v->b, v->c);
    } else if (unused == (void *)(s32)v->d) {
        func_800491FC(v->a, v->b, v->c);
        t->p = (V *)((u8 *)t->p + 8);
    }
}
