/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014BEF8();
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x64]; u16 uAC;
} T;
s32 func_80149B54(T *p) {
    if (p->flags & 0x400) {
        return 0;
    }
    if (func_8014BEF8(p) == 0) {
        return 0;
    }
    if (p->uAC & 0x10) {
        return 1;
    }
    return 0;
}
