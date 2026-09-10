/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x1C8]; s16 u1C8; } T;
void func_8014ACC0(T *p, s32 a1) {
    p->u1C8 = p->u1C8 - a1;
    if (p->u1C8 < 0) {
        p->u1C8 = 0;
    }
}
