/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x78]; u16 *t; } T;
s32 func_8014CAE4(T *p, s32 a1) {
    return p->t[a1 + 14];
}
