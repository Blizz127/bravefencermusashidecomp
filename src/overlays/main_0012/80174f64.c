/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80175014();
typedef struct {
    u8 pad[0x34]; void *u34;
    u16 u38;
} T;
void func_80174F64(T *p) {
    if (func_80175014(p, p->u34, p->u38 & 0x7FFF)) {
        p->u38 |= 0x8000;
    } else {
        p->u38 = p->u38 + 1;
    }
}
