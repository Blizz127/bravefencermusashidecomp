/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80114F30, D_80114F34, D_80114F38;
extern s32 D_80114F24, D_80114F28, D_80114F2C;
extern u8 D_8012694C;
extern s16 D_8018534C;
extern s16 D_801853C4, D_801853C6, D_801853C8;
extern s16 D_801853BC, D_801853BE, D_801853C0;
void func_8017B7A8(void) {
    D_8012694C = 1;
    D_8018534C = 0;
    D_801853C4 = D_80114F30;
    D_801853C6 = D_80114F34;
    D_801853C8 = D_80114F38;
    D_801853BC = D_80114F24;
    D_801853BE = D_80114F28;
    D_801853C0 = D_80114F2C;
}
