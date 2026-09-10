/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014ED28();
void func_80146D90();
s32 func_8014CC28();
s32 func_8014FA04();
typedef struct { u8 pad[0x34]; s32 u34; } T;
s32 func_801615C4(T *p, s32 a1) {
    s32 r = 0;
    if ((a1 & 1) == 0) {
        if (func_8014ED28(p)) {
            func_80146D90(p);
        }
    }
    if (p->u34 > 0) {
        r |= func_8014CC28(p);
    }
    return r | func_8014FA04(p);
}
