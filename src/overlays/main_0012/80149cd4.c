/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x62]; u16 uAA;
    u8 padAC[0x11C]; s16 u1C8;
} T;
s32 func_80149CD4(T *p) {
    if (p->flags & 0x404) {
        return 0;
    }
    if (p->u1C8) {
        return 0;
    }
    if (p->uAA & 8) {
        return 1;
    }
    return 0;
}
