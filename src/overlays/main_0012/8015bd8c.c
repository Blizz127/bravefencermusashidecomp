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
} T;
void func_8015BD8C(T *p) {
    func_801553A8(p);
    func_80154A74(p, 17);
    p->flags &= -3;
}
