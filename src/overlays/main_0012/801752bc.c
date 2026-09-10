/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801553A8();
void func_80154A74();
typedef struct {
    u8 pad_0[68];
    u32 flags;
    u8 pad_48[174];
    s16 fF6;
} T;
void func_801752BC(T *p) {
    p->fF6 = 4096;
    func_801553A8(p);
    func_80154A74(p, 17);
    p->flags &= -3;
}
