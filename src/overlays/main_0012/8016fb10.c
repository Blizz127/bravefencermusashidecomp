/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171CC4();
void func_80171990();
extern u8 D_8011F738;
void func_8016FB10(void *p) {
    if (func_80171CC4(p, &D_8011F738)) {
        func_80171990(p);
    }
}
