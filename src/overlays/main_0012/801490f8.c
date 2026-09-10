/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80012B04();
typedef struct {
    u8 pad[0x100]; s16 x, y, z; s16 pad106; s16 tx, ty, tz;
} T;
void func_801490F8(T *p, s32 a1) {
    s16 s = a1;
    p->x += func_80012B04(p->x, p->tx, s);
    p->y += func_80012B04(p->y, p->ty, s);
    p->z += func_80012B04(p->z, p->tz, s);
}
