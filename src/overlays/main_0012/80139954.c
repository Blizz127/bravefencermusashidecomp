#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8013A8B0(s32);                               /* static */
extern s32 D_801269F0;
extern s16 D_801269F4;
extern u16 D_80126A08;
extern s32 D_80126A30;

void func_80139954(void) {
    D_801269F4 = 0;
    D_801269F0 = 0;
    if ((D_80126A08 != 0) && (D_80126A30 != 0)) {
        func_8013A8B0(D_80126A30);
    }
}
