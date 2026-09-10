/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_801801A0[];
void func_80019064();
extern s32 D_80180178;
extern s16 D_8011DB0C;
extern s16 D_8011F748;
typedef struct { u8 pad[2]; u16 idx; } T;
void func_80153CCC(T *p) {
    func_80019064(&D_80180178);
    D_801801A0[p->idx](p);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}
