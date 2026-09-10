/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014EE14();
typedef struct {
    u8 pad[6]; u16 u6; u8 pad8[2]; u16 uA; u8 padC[2]; u16 uE;
    u8 pad10[0x34]; s32 flags;
    u8 pad48[0x40]; u16 u88, u8A, u8C;
    u8 pad8E[0x16A]; s32 u1F8;
} T;
s32 func_8014ED80(T *p) {
    s16 x[4];
    s16 y[4];
    if (p->flags & 0x80000) {
        return 0;
    }
    if (p->u1F8 & 0x4000000) {
        return 0;
    }
    x[0] = p->u88;
    x[1] = p->u8A - 0x10;
    x[2] = p->u8C;
    y[0] = p->u6;
    y[1] = p->uA - 0x10;
    y[2] = p->uE;
    return func_8014EE14(p, x, y);
}
