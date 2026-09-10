/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 x, y, z, pad; } S;
extern S D_80126B38;
void func_801734BC();
void func_80173460(void *p, S *q) {
    func_801734BC(p);
    D_80126B38 = *q;
    D_80126B38.pad = 1;
}
