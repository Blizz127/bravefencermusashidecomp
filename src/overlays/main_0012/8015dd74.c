/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014C1A0();
void func_80015978();
s32 func_80029AAC();
void func_8014C4AC();
typedef struct Inner { u8 pad[0x12]; s16 u12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x154]; void *u178;
} T;
void func_8015DD74(T *p) {
    s16 tmp[4];
    void *q = p->u178;
    s32 v;
    if (q == 0) {
        return;
    }
    func_8014C1A0(p, q);
    func_80015978((u8 *)q + 4, tmp);
    tmp[3] = 0;
    v = func_80029AAC();
    func_8014C4AC(q, 9, v, tmp, p->inner->u12);
    p->u178 = 0;
}
