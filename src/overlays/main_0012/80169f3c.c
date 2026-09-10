/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800D1FC8();
s32 func_800D21C4();
void func_80128EA8();
void func_80146C3C();
extern s32 D_80181410;
extern s32 D_801813D0;
typedef struct {
    u8 pad[4]; s32 u4;
    u8 pad8[0x10]; s16 u18, u1A;
    u8 pad1C[8]; u8 u24, u25, u26;
} U;
typedef struct { u8 pad[2]; u16 u2; u8 pad4[0x1C]; U *inner; } T;
void func_80169F3C(T *p) {
    U *v;
    func_800D1FC8(p, 6);
    v = (U *)func_800D21C4(p, &D_80181410, 0x16);
    if (v) {
        p->inner = v;
        v->u1A = 0x2000;
        v->u18 = 0x2000;
        v->u26 = 0x60;
        v->u25 = 0x60;
        v->u24 = 0x60;
        v->u4 |= 0x50000000;
        func_80128EA8(v, (u8 *)p + 0x24, &D_801813D0);
        p->u2++;
    } else {
        func_80146C3C(p);
    }
}
