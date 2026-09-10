/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80128EA8();
extern u8 D_8017FB8C[];
extern void *D_8017FC88[];
typedef struct {
    u8 pad[4]; s32 u4;
    u8 pad8[0x10]; s16 u18, u1A;
    u8 pad1C[4]; void *u20;
    u8 pad24[3]; u8 u27;
} Inner;
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x1C]; Inner *inner;
    u8 pad24[0x10]; u16 u34;
} T;
void func_8014358C(T *p) {
    Inner *in;
    u16 v;
    p->inner->u20 = D_8017FB8C;
    in = p->inner;
    if (in->u4 == 0) {
        in->u4 = 0x50000000;
    }
    p->inner->u27 = 0x90;
    v = p->u34 & 0x7FFF;
    if (v) {
        in = p->inner;
        in->u1A = v;
        in->u18 = v;
    }
    func_80128EA8(p->inner, (u8 *)p + 0x24, D_8017FC88[p->u34 & 3]);
    p->u2 = p->u2 + 1;
}
