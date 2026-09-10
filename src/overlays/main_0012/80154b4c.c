/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154B7C();
typedef struct { u8 pad[0xD0]; s32 d0; } T;
void func_80154B4C(T *p, s32 a1) {
    if (p->d0 != a1) {
        func_80154B7C(p, a1);
    }
}
