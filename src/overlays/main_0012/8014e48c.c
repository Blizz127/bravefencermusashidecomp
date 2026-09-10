/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014E5B4();
void func_8014E514();
typedef struct {
    u8 pad[6]; u16 a; u8 pad8[2]; u16 b; u8 padC[2]; u16 c;
    u8 pad10[0x78]; u16 u88, u8A, u8C;
    u8 pad8E[0xEE]; s32 u17C;
} T;
void func_8014E48C(T *p) {
    s16 x[4];
    s16 y[4];
    x[0] = p->u88;
    x[1] = p->u8A;
    x[2] = p->u8C;
    y[0] = p->a;
    y[1] = p->b;
    y[2] = p->c;
    if (p->u17C == 0) {
        func_8014E5B4(p, x, y);
    } else {
        func_8014E514(p, x, y);
    }
}
