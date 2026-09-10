/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A1C();
void func_80174650();
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_801739D8(T *p) {
    if (!(p->flags & 2)) {
        func_80171A1C(p);
        func_80174650(p);
    }
}
