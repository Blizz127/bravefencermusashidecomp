#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80146CA0(s32);                               /* static */
void func_80154150(s32, s32);                            /* static */
void func_801553A8();                                  /* static */
extern s32 D_8011F730;

void func_8015F848(s32 arg0) {
    func_801553A8();
    func_80154150(arg0, 0x1F);
    D_8011F730 |= 5;
    func_80146CA0(arg0);
}
