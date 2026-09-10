/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[4]; s16 u4; u8 pad6[2]; s32 u8; } T;
void func_80138C30(T *p) {
    if (p->u4 == 4) {
        p->u4 = 2;
    } else {
        p->u8 |= 0x800;
    }
}
