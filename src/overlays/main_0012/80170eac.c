#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_800D0F8C(u8);                              /* extern */
void func_801718AC(s32);                               /* static */
extern u8 D_8011F738;
extern s32 D_8011F73C;
extern s32 D_8011F740;

void func_80170EAC(void) {
    s32 var_a0;

    if (func_800D0F8C(D_8011F738) != 0) {
        var_a0 = D_8011F73C;
    } else {
        var_a0 = D_8011F740;
    }
    func_801718AC(var_a0);
}
