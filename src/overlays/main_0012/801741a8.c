#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8014B2A8();                                  /* static */
void func_8014BB0C();                                  /* static */
void func_8014BDC8();                                  /* static */
extern s32 D_80078EA4;
extern s32 D_80078ED8;

void func_801741A8(void) {
    func_8014BDC8();
    func_8014BB0C();
    func_8014B2A8();
    D_80078ED8 = 0xA00000;
    D_80078EA4 = 0xA00000;
}
