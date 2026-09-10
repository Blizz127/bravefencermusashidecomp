/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014E83C();
void func_8014E790();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[0x78]; s16 u88, u8A, u8C;
    u8 pad8E[0xF2]; s32 u180;
} T;
void func_8014E6F8(T *p) {
    s16 x[4];
    s16 y[4];
    x[0] = p->u88;
    x[1] = p->u8A;
    x[2] = p->u8C;
    y[0] = p->u6;
    y[1] = p->uA;
    y[2] = p->uE;
    if (p->u180 == 0) {
        x[1] -= 0x54;
        y[1] -= 0x54;
        func_8014E83C(p, x, y);
        return;
    }
    func_8014E790(p, x, y);
}
