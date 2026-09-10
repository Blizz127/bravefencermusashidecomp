/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x4E]; u8 u4E; } T;
void func_8014BFF4(T *p, s32 a1) {
    if (p->u4E == 0) {
        p->u4E = a1;
    }
}
