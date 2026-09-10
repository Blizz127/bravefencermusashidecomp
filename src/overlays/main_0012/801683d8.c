/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80166994();
s32 func_80166690();
void func_80146C3C();
typedef struct { u8 pad[0x28]; s16 a; u8 pad2A[2]; s16 b; } T;
void func_801683D8(T *p) {
    func_80166994(p, 2, p->b, 0);
    if ((s16)func_80166690(p->b, p->a) == 0) {
        func_80146C3C(p);
    }
}
