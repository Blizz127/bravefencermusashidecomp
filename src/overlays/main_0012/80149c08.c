/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014BEF8();
s32 func_80029178();
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x64]; u16 uAC;
    u8 padAE[0x11A]; s16 u1C8;
    u8 pad1CA[0x59]; u8 u223;
} T;
s32 func_80149C08(T *p) {
    if (p->u223) {
        return 0;
    }
    if (p->u1C8) {
        return 0;
    }
    if (p->flags & 0x404) {
        return 0;
    }
    if (func_8014BEF8(p) == 0) {
        return 0;
    }
    if ((func_80029178(0x89) & 0xFF) == 0) {
        return 0;
    }
    if (p->uAC & 0x10) {
        return 1;
    }
    return 0;
}
