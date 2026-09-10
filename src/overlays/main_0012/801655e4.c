/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80078EC1;
s32 func_80165658();
void func_8014BD60();
void func_801655E4(void *p) {
    s32 v = func_80165658(p, D_80078EC1 & 0x7F);
    func_8014BD60(p, v & 0x7F);
}
