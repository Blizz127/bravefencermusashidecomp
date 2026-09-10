/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8012A418();
extern u16 D_80126B5E, D_80126B62, D_80126B66;
extern s16 D_80185C08, D_8018534C, D_801853CC, D_801853CE, D_801853D0;
void func_8017B1D8(void) {
    func_8012A418();
    D_80185C08 = 0;
    D_8018534C = 0;
    D_801853CC = D_80126B5E;
    D_801853CE = D_80126B62;
    D_801853D0 = D_80126B66;
}
