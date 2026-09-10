/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014C59C();
s32 func_80012A60();
typedef struct Inner { u8 pad[0x12]; s16 unk12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
s32 func_8014C2B0(T *p, s32 a1, u32 a2) {
    s32 v = func_8014C59C(p, a1);
    return (s16)func_80012A60((s16)v, p->inner->unk12) < (s32)(a2 & 0xFFFF);
}
