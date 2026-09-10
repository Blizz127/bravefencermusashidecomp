/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154A74();
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_80155F80(T *p) {
    p->flags &= ~2;
    func_80154A74(p, 0x11);
}
