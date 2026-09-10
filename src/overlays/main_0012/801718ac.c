#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80171A1C(void *, s32);                            /* static */
extern s32 *D_80126B58;
extern s32 D_80126D50;
extern s32 *D_80126D54;
extern s8 D_80126D6C;

void func_801718AC(s32 *arg0) {
    D_80126D54 = arg0;
    D_80126D6C = 0;
    D_80126D50 = *arg0 | (D_80126D50 & 0x7F000000);
    func_80171A1C(&D_80126B58, 0x7F000000);
}
