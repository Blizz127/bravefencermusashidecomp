/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 x, y, z; } SVEC;
typedef struct { s32 x, y, z; } VEC;
void func_80049324();
s32 func_800132BC(SVEC *a, SVEC *b) {
    VEC d;
    VEC out;
    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    func_80049324(&d, &out);
    return out.x + out.y + out.z;
}
