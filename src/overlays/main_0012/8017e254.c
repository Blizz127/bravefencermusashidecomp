/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_801827D8[];
extern s16 D_80185B00;
extern s16 D_80185B02;
s32 func_8017E254(void) {
    D_801827D8[D_80185B00]();
    return D_80185B02 < 0;
}
