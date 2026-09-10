/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Inner { u8 pad[0x14]; u16 a; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_801477C8(T *p, s32 a1) {
    p->inner->a = (p->inner->a + a1) & 0xFFF;
}
