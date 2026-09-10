/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8012C194();
void func_8012CAE4();
void func_8001CB6C();
extern u8 D_8017FC98[];
typedef struct {
    u8 pad[4]; s32 u4;
    s16 u8, uA, uC;
    u8 padE[2]; s16 u10;
    u8 pad12[6]; s16 u18, u1A;
    u8 pad1C[0xB]; u8 u27;
} Q;
typedef struct {
    u8 pad[6]; u16 u6;
    u8 pad8[2]; u16 uA;
    u8 padC[2]; u16 uE;
    u8 pad10[0x26]; u16 u36;
} R;
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x60]; R *u64;
    u8 pad68[8]; s16 u70;
    u8 pad72[0x5A]; Q *uCC;
    u8 padD0[0x2C]; u16 uFC;
} T;
void func_80144364(T *p) {
    Q *q = func_8012C194(p);
    s16 v;
    if (q == 0) {
        func_8012CAE4(p);
        return;
    }
    p->uFC = p->u64->u36;
    p->uCC = q;
    func_8001CB6C(q, D_8017FC98, 0x250, 0x1A0);
    q->u4 = 0x60000000;
    q->u27 = 0x14;
    q->u10 = 0x400;
    q->u8 = p->u64->u6;
    q->uA = p->u64->uA;
    q->uC = p->u64->uE;
    v = p->u70;
    if (v) {
        q->u1A = v;
        q->u18 = v;
    } else {
        q->u1A = 0x2000;
        q->u18 = 0x2000;
    }
    p->u2 = 1;
}
