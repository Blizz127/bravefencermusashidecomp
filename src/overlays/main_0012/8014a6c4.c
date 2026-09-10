/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029178();
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x176]; u8 u1BE;
} T;
s32 func_8014A6C4(T *p) {
    if ((func_80029178(0x1F) & 0xFF) == 0) {
        return 0;
    }
    if (p->flags & 4) {
        return 0;
    }
    if (p->u1BE == 0) {
        return 1;
    }
    return 0;
}
