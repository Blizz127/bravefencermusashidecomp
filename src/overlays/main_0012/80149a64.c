/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80149AA8();
s32 func_80149B54();
s32 func_80149A64(void *p) {
    if (func_80149AA8(p) || func_80149B54(p)) {
        return 1;
    }
    return 0;
}
