/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154BC8();
typedef struct { u8 pad[0xD0]; s32 d0; } T;
void func_80154B98(T *p, s32 a1, s32 a2) {
    if (p->d0 != a1) {
        func_80154BC8(p, a1, a2);
    }
}
