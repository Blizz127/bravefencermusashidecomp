#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80146994(s32, s32, s32, s32);                      /* static */
void func_80147324();                                 /* static */
void func_8014B2F8(s32);                               /* static */

void func_8015086C(s32 arg0) {
    func_80146994(0x48, arg0, 0, 0);
    func_8014B2F8(arg0);
    func_80147324(0xA1B);
}
