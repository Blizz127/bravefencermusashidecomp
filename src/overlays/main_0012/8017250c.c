/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80172560();
typedef struct { u16 a, b, c; } V;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[6]; u16 uE;
} T;
s32 func_8017250C(T *p, V *v) {
    if (func_80172560(p, v) == 0) {
        return 0;
    }
    p->u6 = v->a;
    p->uE = v->c;
    return 1;
}
