/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8012F14C();
void func_8012EFB8();
typedef struct { u8 pad[0x20]; u8 *inner; } T;
void func_80149584(T *p, void *a1, void *a2) {
    s16 tmp[4];
    func_8012F14C(p->inner + 0x34, a1, tmp);
    func_8012EFB8(tmp, a2);
}
