/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8012C194();
void func_8012CAE4();
void func_8001CC3C();
void func_80128EA8();
extern u8 D_800D387C[];
extern u8 D_800D3888[];
typedef struct {
    u8 pad[4]; s32 u4;
    u8 pad8[0]; s16 u8, uA, uC;
    u8 padE[0xA]; s16 u18, u1A;
    u8 pad1C[4]; void *u20;
    u8 pad24[3]; u8 u27;
} Q;
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[2]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
    u8 pad10[0xBC]; Q *uCC;
} T;
void func_801446A4(T *p) {
    Q *q = func_8012C194(p);
    if (q == 0) {
        func_8012CAE4(p);
        return;
    }
    p->uCC = q;
    func_8001CC3C(q, 0, 0, 0);
    q->u20 = D_800D387C;
    q->u27 = 0x9C;
    q->u1A = 0x3000;
    q->u18 = 0x3000;
    q->u4 = q->u4 | 0x50000000;
    func_80128EA8(q, (u8 *)p + 0xD0, D_800D3888);
    q->u8 = p->u6;
    q->uA = p->uA;
    q->uC = p->uE;
    p->u2 = p->u2 + 1;
}
