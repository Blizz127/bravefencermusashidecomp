/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 a, b; u8 pad[3]; u8 e, f; } G;
extern G D_8011F7A8;
void func_80175454(void) {
    if (D_8011F7A8.a == 0) {
        D_8011F7A8.a = 1;
        D_8011F7A8.b = 0;
        D_8011F7A8.e = 0xA;
        D_8011F7A8.f = 0;
    }
}
