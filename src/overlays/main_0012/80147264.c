/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u16 x, y, z; } V;
extern V D_80126BB8;
void func_80147264(V *p) {
    D_80126BB8.x = p->x;
    D_80126BB8.y = p->y;
    D_80126BB8.z = p->z;
}
