/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern void *D_8011F738;
extern s32 D_800D59EC;
extern s32 D_80126B58;
void func_80170AD8();
void func_80171904();
void func_80170B48();
void func_80170970(void) {
    D_8011F738 = &D_800D59EC;
    func_80171904(func_80170AD8);
    func_80170B48(&D_80126B58);
}
