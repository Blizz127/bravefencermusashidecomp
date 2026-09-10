#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8002A4FC();                                /* extern */

s32 func_8012EECC(s32 arg0) {
    return arg0 - ((arg0 * func_8002A4FC() * 0x64) / 7680);
}
