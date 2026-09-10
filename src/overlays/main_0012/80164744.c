/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80162D28();
typedef void (*CB)();
extern CB D_80180F84[];
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x1C]; void *inner;
} T;
void func_80164744(T *p) {
    void *in = p->inner;
    D_80180F84[p->u2]();
    if (in) {
        func_80162D28(p);
    }
}
