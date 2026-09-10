#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8002D4C8(u16, u16);                          /* extern */
void func_80171928(s32);                               /* static */
extern u16 D_8011F738;
extern u16 D_8011F73A;

void func_801710DC(s32 arg0) {
    func_8002D4C8(D_8011F738, D_8011F73A);
    func_80171928(arg0);
}
