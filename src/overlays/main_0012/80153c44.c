/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80153C74();
extern s16 D_8011DB18;
void func_80153C44(void *a0, void *a1, s32 a2) {
    func_80153C74(a0, a1, a2);
    D_8011DB18 = a2;
}
