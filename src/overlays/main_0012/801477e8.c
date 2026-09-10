/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x34]; s32 u34; } T;
void func_801477E8(T *p, s32 a1) {
    p->u34 = a1;
    if (a1 < (s32)0xFFE10000) {
        p->u34 = 0xFFE10000;
    } else if (a1 > 0x1F0000) {
        p->u34 = 0x1F0000;
    }
}
