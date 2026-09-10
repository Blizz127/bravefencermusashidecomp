/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154A74();
void func_801553C0();
void func_801553A8();
typedef struct {
    u8 pad_0[68];
    u32 flags;
} T;
void func_801585EC(T *p) {
    p->flags &= -3;
    func_80154A74(p, 17);
    func_801553C0(p);
    func_801553A8(p);
}
