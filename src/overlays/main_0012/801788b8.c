/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8012C658();
void func_8012E8E0();
void func_8012B2CC();
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
    u8 pad10[0x10]; Inner *inner;
    u8 pad24[0x4C]; s16 u70;
} T;
typedef struct {
    u8 pad[0x64]; void *u64;
    u8 pad68[0x74]; void *uDC;
} R;
R *func_801788B8(T *p, void *a1) {
    s16 vec[4];
    R *q = func_8012C658(0x83, p->u70, 0);
    if (q == 0) {
        return 0;
    }
    q->u64 = p;
    vec[0] = p->u6;
    vec[1] = p->uA;
    vec[2] = p->uE;
    if (p->inner) {
        vec[3] = p->inner->u12;
    } else {
        vec[3] = 0;
    }
    func_8012E8E0(q, vec);
    func_8012B2CC(q);
    q->uDC = a1;
    return q;
}
