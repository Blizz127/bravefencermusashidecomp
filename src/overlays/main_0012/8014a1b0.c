/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80015978();
s32 func_80156370();
void func_8014C4AC();
typedef struct Inner { u8 pad[0x12]; s16 u12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_8014A1B0(T *p, void *a1) {
    s16 tmp[4];
    s32 v;
    func_80015978((u8 *)p + 4, tmp);
    tmp[3] = 0;
    v = func_80156370(0xA);
    func_8014C4AC(a1, 0xA, (u16)v, tmp, p->inner->u12);
}
