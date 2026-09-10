/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8016F1AC();
extern s16 D_800B9A08;
s32 func_80149884(void) {
    if (D_800B9A08 != 0x308F) {
        return func_8016F1AC() == 0;
    }
    return 0;
}
