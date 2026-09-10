/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171AB0();
void func_80171928();
extern u8 D_8011F738;
void func_801702B8(void *p) {
    if ((s16)func_80171AB0(p, &D_8011F738) == 0) {
        func_80171928(p);
    }
}
