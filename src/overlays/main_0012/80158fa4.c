/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80148800();
s32 func_801399F0();
void func_80139914();
s32 func_80159464();
void func_801594E8();
void func_80146C98();
void *func_8013767C();
void func_80146CA0();
extern s32 D_80184298;
extern s32 D_80110C3C;
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x174]; void *u198;
} T;
void func_80158FA4(T *p) {
    s16 v;
    Inner *in = p->inner;
    in->u12 = (in->u12 + 0x16) & 0xFFF;
    if (func_80148800(p) & 0xF0) {
        D_80184298 = 1;
    }
    if (func_801399F0(p->u198) == 0) {
        return;
    }
    func_80139914(p->u198);
    p->u198 = 0;
    v = func_80159464(p);
    if (v) {
        func_801594E8(p, v);
        func_80146C98(p, 0xC);
    } else {
        p->u198 = func_8013767C(&D_80110C3C);
        func_80146CA0(p);
    }
}
