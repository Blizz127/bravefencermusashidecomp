/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012DEB8();
extern s16 D_80126B98;
s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3) {
    if (func_8012DEB8(a0, a1, a2, a3) != 0) {
        D_80126B98 = a3;
        return 1;
    }
    return 0;
}
