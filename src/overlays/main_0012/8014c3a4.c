/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014C43C();
typedef struct Inner { u8 pad[0x12]; s16 unk12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_8014C3A4(T *p, s32 a1, s32 a2, s32 a3) {
    func_8014C43C(p, a1, a2, a3, p->inner->unk12);
}
