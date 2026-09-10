/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80013294();
extern s16 D_80126B5E, D_80126B62, D_80126B66;
typedef struct {
    u8 pad[6]; s16 u6;
    u8 pad8[2]; s16 uA;
    u8 padC[2]; s16 uE;
    u8 pad10[0xBC]; s32 uCC;
    u8 padD0[0x2C]; s16 uFC;
} T;
s32 func_80144B14(T *p) {
    s16 a[4];
    s16 b[4];
    a[0] = p->u6;
    a[1] = p->uA;
    a[2] = p->uE;
    b[0] = D_80126B5E;
    b[1] = D_80126B62;
    b[2] = D_80126B66;
    if (func_80013294(a, b) < p->uFC) {
        return p->uCC;
    }
    return 0;
}
