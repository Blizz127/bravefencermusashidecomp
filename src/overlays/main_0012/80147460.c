/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[8]; s32 a; u8 padC[0x28]; s32 b; } T;
void func_80147460(T *p) {
    p->a += p->b;
}
