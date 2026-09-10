/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 *D_8006B54C;
extern s32 D_8006B574;
s32 func_8003AFF0(s32 a0, s32 a1) {
    u16 v = D_8006B54C[a0];
    if (a1 == -1) {
        return v;
    }
    return v << D_8006B574;
}
