/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8018071C[];
void func_80149020();
typedef struct { u8 pad[0x4F]; u8 idx; } T;
void func_80158880(T *p) {
    func_80149020(p);
    D_8018071C[p->idx](p);
}
