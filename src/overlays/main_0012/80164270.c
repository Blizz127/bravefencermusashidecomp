/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80146CA0(s32);                               /* static */
void func_80146E90(s32, s32);                            /* static */
void func_80162D88();                                  /* static */

void func_80164270(s32 arg0) {
    func_80162D88();
    func_80146E90(arg0, 0x20);
    func_80146CA0(arg0);
}
