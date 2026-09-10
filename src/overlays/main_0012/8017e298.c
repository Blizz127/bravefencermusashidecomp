/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029504();
void func_8017C008();
extern s16 D_80185B08;
extern u16 D_80185B00;
void func_8017E298(void) {
    s32 v = func_80029504();
    u16 *p;
    if ((u32)(v - 5) >= 0x4B5) {
        if (v != 0x6A4) {
            D_80185B08 = 1;
        } else {
            D_80185B08 = 2;
        }
    } else {
        D_80185B08 = 0;
    }
    func_8017C008(1, D_80185B08);
    p = &D_80185B00;
    *p = *p + 1;
}
