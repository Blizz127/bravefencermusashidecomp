/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801724EC();
typedef struct { u16 a, b, c; } V;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
} T;
s32 func_8017248C(T *p, V *v) {
    if (func_801724EC(p, v) == 0) {
        return 0;
    }
    p->u6 = v->a;
    p->uA = v->b;
    p->uE = v->c;
    return 1;
}
