/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801491C4();
typedef struct Inner { u8 pad[0x12]; u16 unk12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
s32 func_80149184(T *p) {
    return (p->inner->unk12 - func_801491C4(p)) & 0xFFF;
}
