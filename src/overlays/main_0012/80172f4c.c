#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80154A74(void *, s32);                            /* static */
void func_8017303C(void *);                               /* static */
void func_80174650(void *);                               /* static */
extern s32 *D_800D47F4;
extern s16 D_80126B30;
extern s32 *D_80126B58;

void func_80172F4C(void) {
    func_8017303C(&D_800D47F4);
    func_80154A74(&D_80126B58, 0x13);
    D_80126B30 = 0;
    func_80174650(&D_80126B58);
}
