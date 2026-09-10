/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8011F738;
void func_801719A4();
void func_80171990();
void func_801707D4();
void func_80170784(void *p) {
    func_801719A4(p, 1);
    D_8011F738();
    func_80171990(p);
    func_801707D4(p);
}
