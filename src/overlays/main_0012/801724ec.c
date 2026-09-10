/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_80013450(s32);                             /* extern */

s32 func_801724EC(s32 arg0) {
    return func_80013450(arg0 + 4) < 0x10;
}
