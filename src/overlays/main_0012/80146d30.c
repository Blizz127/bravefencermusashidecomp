/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s32 x, y, z; } V;
extern V D_80127090;
typedef struct { u8 pad[0x10]; s32 x, y, z; } T;
void func_80146D30(T *p) {
    p->x = D_80127090.x;
    p->y = D_80127090.y;
    p->z = D_80127090.z;
    D_80127090.x = 0;
    D_80127090.y = 0;
    D_80127090.z = 0;
}
