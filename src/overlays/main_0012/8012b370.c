/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80049A1C();
typedef struct {
    u8 pad[8]; s16 u8, uA, uC;
    u8 padE[0x1E]; u16 u2C;
    u8 pad2E[0x1A]; s32 u48, u4C, u50;
} Inner;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
    u8 pad10[0x10]; Inner *inner;
    u8 pad24[0x2C]; u16 u50, u52, u54;
} T;
void func_8012B370(T *p) {
    Inner *in = p->inner;
    Inner *q;
    s16 v;
    if (in) {
        func_80049A1C((u8 *)in + 0x10, (u8 *)in + 0x34);
        q = p->inner;
        v = p->u6 + p->u50;
        q->u8 = v;
        q->u48 = v;
        v = p->uA + p->u52;
        q->uA = v;
        q->u4C = v;
        v = p->uE + p->u54;
        q->uC = v;
        q->u2C = q->u2C | 1;
        q->u50 = v;
    }
}
