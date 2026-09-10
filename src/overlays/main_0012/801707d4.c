/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80171928(s32);                               /* static */
s32 func_80174ED4();                                /* static */

void func_801707D4(s32 arg0) {
    if ((func_80174ED4() << 0x10) != 0) {
        func_80171928(arg0);
    }
}
