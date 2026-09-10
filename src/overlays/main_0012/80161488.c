/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801615C4();
s32 func_80161774();
s32 func_8016197C();
typedef struct { u8 pad[0x1C6]; u8 u1C6; } T;
s32 func_80161488(T *p) {
    s32 v = func_801615C4(p, 0);
    if (p->u1C6) {
        return func_8016197C(p, v) & ~7;
    }
    return func_80161774(p, v);
}
