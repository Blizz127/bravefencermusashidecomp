/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016BF50();
void func_8016BFA8();
void func_80146C3C();
extern s32 D_801847F4;
extern s32 D_801847F8;
typedef struct Inner { u8 pad[0x12]; u16 ang; u8 pad14[6]; s16 u1A; } Inner;
typedef struct { u8 pad[0x10]; s16 u10; u8 pad12[0xE]; Inner *inner; } T;
void func_8016BEA0(T *p) {
    Inner *in = p->inner;
    func_8016BF50(p);
    p->u10 -= 0x18;
    in->u1A += p->u10;
    in->ang = (in->ang + 0x22) & 0xFFF;
    func_8016BFA8(p, &D_801847F4, &D_801847F8, (u8 *)in + 0x18);
    if (in->u1A < 0) {
        func_80146C3C(p);
    }
}
