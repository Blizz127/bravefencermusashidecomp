/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x10]; s32 x, y, z; } T;
void func_801473DC(T *p) {
    p->z = 0;
    p->y = 0;
    p->x = 0;
}
