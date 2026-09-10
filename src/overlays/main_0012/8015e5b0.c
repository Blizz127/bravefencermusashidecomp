/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80133784();
void func_80015978();
void func_8014C4AC();
typedef struct Inner { u8 pad[0x12]; s16 u12; } Inner;
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
} Q;
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[0x10]; Inner *inner;
    u8 pad24[0x168]; Q *u18C;
} T;
void func_8015E5B0(T *p) {
    s16 a[4];
    s16 b[4];
    Q *q = p->u18C;
    if (q == 0) {
        return;
    }
    a[0] = p->u6;
    a[1] = p->uA - 0x14;
    a[2] = p->uE;
    b[0] = q->u6;
    b[1] = q->uA;
    b[2] = q->uE;
    if (func_80133784(0, a, b)) {
        q->u6 = b[0];
        q->uA = b[1];
        q->uE = b[2];
    }
    func_80015978((u8 *)q + 4, a);
    a[3] = 0;
    func_8014C4AC(q, 0x1C, 0, a, p->inner->u12);
    p->u18C = 0;
}
