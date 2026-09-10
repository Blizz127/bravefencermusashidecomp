/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8015430C();
typedef struct { u8 pad[0xB4]; s32 b4; } T;
void func_801542DC(T *p, s32 a1) {
    if (p->b4 != a1) {
        func_8015430C(p, a1);
    }
}
