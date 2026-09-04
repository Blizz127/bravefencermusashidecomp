#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012AD80();                                  /* static */
s32 func_8012BEE8(s32);                             /* static */
void func_801319E0(s32);                               /* static */

void func_80130858(s32 arg0) {
    func_8012AD80();
    if (func_8012BEE8(arg0) != 0) {
        func_801319E0(arg0);
    }
}
