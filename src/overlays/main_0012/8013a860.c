#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80016714(void *, s32);                            /* extern */
extern s32 *D_8011DA80;

void func_8013A860(void) {
    void *var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = &D_8011DA80;
    do {
        func_80016714(var_s0, 0x10);
        var_s1 += 1;
        var_s0 += 0x10;
    } while (var_s1 < 2);
}
