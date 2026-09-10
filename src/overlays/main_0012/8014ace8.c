/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014AD30();
typedef struct { u8 pad[6]; s16 x; u8 pad8[2]; s16 y; u8 padC[2]; s16 z; } T;
void func_8014ACE8(T *p, void *a1, void *a2) {
    s16 sp[3];
    sp[0] = p->x;
    sp[1] = p->y - 0x20;
    sp[2] = p->z;
    func_8014AD30(p, sp, a1, a2);
}
