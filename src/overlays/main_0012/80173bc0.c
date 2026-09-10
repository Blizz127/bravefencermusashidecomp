#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_800D0EC4();                                /* extern */
void func_8013E588();                                  /* static */
void func_80171A1C(s32);                               /* static */
void func_80171A34(s32, s32);                            /* static */
void func_80174650(s32);                               /* static */
extern s16 D_8011F9C8;
extern s16 D_80126B38;
extern s16 D_80126B3A;

void func_80173BC0(s32 arg0) {
    if ((D_80126B3A != 0) && (D_80126B3A < 0x6F) && (func_800D0EC4() == 0)) {
        if (D_80126B38 & 0x8000) {
            func_8013E588();
            goto block_6;
        }
        func_80174650(arg0);
        D_8011F9C8 = 2;
        func_80171A34(arg0, 7);
        return;
    }
block_6:
    func_80171A1C(arg0);
}
