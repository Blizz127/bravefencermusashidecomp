#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012AD50(s32);                               /* static */
s32 func_8012BEE8();                                /* static */

void func_80142740(s32 arg0) {
    if (func_8012BEE8() != 0) {
        func_8012AD50(arg0);
    }
}
