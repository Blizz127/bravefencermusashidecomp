/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_801659DC(void *);                               /* static */
extern u8 D_80078EC1;
extern s32 *D_80126B58;
extern u8 D_80126CF8;

void func_8016533C(void) {
    D_80126CF8 = D_80078EC1;
    func_801659DC(&D_80126B58);
}
