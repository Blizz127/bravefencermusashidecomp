/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8012913C();
typedef struct { u16 a, b, c; } V;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
} T;
T *func_801290DC(u16 a0, V *v) {
    T *q = func_8012913C(a0);
    if (q) {
        q->u6 = v->a;
        q->uA = v->b;
        q->uE = v->c;
    }
    return q;
}
