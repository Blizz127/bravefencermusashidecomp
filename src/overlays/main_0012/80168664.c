/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80049F3C();
void func_80048EAC();
void func_801670E4();
typedef struct { s32 a, b, c, d, e, f, g, h; } M;
extern M D_800AE620;
typedef struct { u8 pad[0x20]; u8 *inner; } Q;
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0xC]; u16 u10, u12;
    u8 pad14[8]; s32 u1C;
    u8 pad20[0x10]; s32 u30;
    Q *u34;
    M m;
} T;
void func_80168664(T *p) {
    Q *q = p->u34;
    p->u1C = 0x20;
    p->u10 = 0x80;
    p->u12 = 0;
    p->u30 = 0x1800;
    p->m = D_800AE620;
    func_80049F3C(0x400, &p->m);
    func_80048EAC(q->inner + 0x34, &p->m);
    func_801670E4(p, -6, -0x44, -0x18);
    p->u2 = p->u2 + 1;
}
