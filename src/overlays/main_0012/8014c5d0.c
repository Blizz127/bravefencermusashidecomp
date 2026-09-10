/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8014C5FC();
extern s32 D_8017FFC8;
s32 func_8014C5D0(void *p, void *q) {
    return (s16)func_8014C5FC(p, q, &D_8017FFC8);
}
