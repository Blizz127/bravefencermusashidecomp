/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014DD8C();
void func_8014D820();
typedef struct {
    u8 pad[6]; u16 u6; u8 pad8[2]; u16 uA; u8 padC[2]; u16 uE;
    u8 pad10[0x78]; u16 u88, u8A, u8C;
    u8 pad8E[0xE2]; s32 u170;
} T;
void func_8014D790(T *p) {
    s16 x[4];
    s16 y[4];
    x[0] = p->u88;
    x[1] = p->u8A - 0x10;
    x[2] = p->u8C;
    y[0] = p->u6;
    y[1] = p->uA - 0x10;
    y[2] = p->uE;
    if (p->u170 == 0) {
        func_8014DD8C(p, x, y);
    } else {
        func_8014D820(p, x, y);
    }
}
