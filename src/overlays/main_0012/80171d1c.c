/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171FFC();
s32 func_8017250C();
void func_80146D90();
s32 func_80171D1C(void *p, void *q, u8 a2) {
    s32 v = func_80171FFC(p, q, a2);
    if (func_8017250C(p, q)) {
        func_80146D90(p);
    }
    return v;
}
