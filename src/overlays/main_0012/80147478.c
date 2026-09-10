/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147514();
void func_80147628();
typedef struct { u8 pad[0x44]; s32 flags; } T;
void func_80147478(T *p) {
    if (!(p->flags & 0x40000000)) {
        func_80147514(p);
        func_80147628(p);
        p->flags |= 0x40000000;
    }
}
