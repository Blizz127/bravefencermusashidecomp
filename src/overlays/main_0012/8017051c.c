/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171928();
extern u16 D_800AE6DC;
typedef struct Inner { u8 pad[0x12]; u16 unk12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_8017051C(T *p) {
    p->inner->unk12 = D_800AE6DC;
    func_80171928(p);
}
