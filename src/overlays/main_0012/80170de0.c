#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80029178(s32);                             /* extern */
void func_801718AC(s32);                               /* static */
extern s32 D_8011F738;
extern s32 D_8011F73C;
extern s32 D_8011F740;

void func_80170DE0(void) {
    s32 var_a0;

    if (func_80029178(D_8011F738) & 0xFF) {
        var_a0 = D_8011F740;
    } else {
        var_a0 = D_8011F73C;
    }
    func_801718AC(var_a0);
}
