/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801553C0();
void func_80154A74();
extern s32 D_8017FD30;
typedef struct Inner { u8 pad[0x10]; s16 u10; } Inner;
typedef struct {
    u8 pad[0xA]; s16 unkA;
    u8 padC[0x14]; Inner *inner;
    u8 pad24[0x14]; void *p38;
    u8 pad3C[0xFC]; s16 u138, u13A, u13C, u13E;
    u8 pad140[0x7D]; u8 u1BD;
} T;
void func_8015D414(T *p) {
    p->u1BD = 8;
    p->p38 = &D_8017FD30;
    p->u138 = 0;
    p->u13A = 0;
    p->u13C = 0;
    p->u13E = 0;
    p->unkA += 0x48;
    p->inner->u10 = 0;
    func_801553C0(p);
    func_80154A74(p, 0x11);
}
