/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Inner { u8 pad[0x12]; u16 a; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_801593E4(T *p) {
    p->inner->a = (p->inner->a + 0x16) & 0xFFF;
}
