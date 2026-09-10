/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016EC0C();
extern u16 D_80181740[];
typedef struct {
    u8 pad0, u1, u2, pad3;
    u16 u4;
} T;
void func_8016EAC0(T *p) {
    p->u4 = p->u4 + D_80181740[p->u2];
    func_8016EC0C(p, 0x80);
    p->u2 = p->u2 + 1;
    if (p->u2 >= 6) {
        p->u2 = 0x20;
        p->u1 = p->u1 + 1;
    }
}
