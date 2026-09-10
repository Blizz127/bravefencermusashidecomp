/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_801553A8();
void func_80155440();
void func_80146CA0();
void func_801746DC();
typedef struct { u16 u0; u8 pad2[0xFA]; u16 uFC; } Q;
typedef struct {
    u8 pad[0x178]; Q *u178;
    u8 pad17C[0xB8]; s32 u234;
} T;
void func_8015D57C(T *p) {
    Q *q;
    func_80154150(p, 0x19);
    func_801553A8(p);
    func_80155440(p);
    func_80146CA0(p);
    p->u234 = 0;
    q = p->u178;
    if (q && q->u0 == 0x1F8) {
        q->uFC = 1;
        func_801746DC(q);
    }
}
