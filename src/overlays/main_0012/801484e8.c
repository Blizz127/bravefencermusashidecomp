#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_801485B8(s32, s32, s32);                       /* static */
s32 func_80154358(void *);                             /* static */
extern s32 *D_80126B58;

void func_801484E8(s32 arg0, s32 arg1) {
    func_801485B8(func_80154358(&D_80126B58) - 0x10, arg0, arg1);
}
