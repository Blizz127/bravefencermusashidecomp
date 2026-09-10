#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_801292C8(void *);                               /* static */
extern s32 *D_8011DB30;

void func_8012927C(void) {
    void *var_s1;
    s32 var_s0;

    var_s1 = &D_8011DB30;
    var_s0 = 0;
    do {
        func_801292C8(var_s1);
        var_s0 += 1;
        var_s1 += 0x38;
    } while (var_s0 < 0x80);
}
