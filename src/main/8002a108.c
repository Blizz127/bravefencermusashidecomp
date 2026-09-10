/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_8002A200();                                /* static */
void func_8002A234();                                  /* static */
s32 func_8002A26C();                                /* static */
s32 func_8002A28C();                                /* static */
s32 func_8002AA00(s32);                             /* static */
extern s32 D_80078EE8;

s32 func_8002A108(s32 arg0) {
    s32 temp_s0;

    temp_s0 = func_8002AA00(func_8002A26C() + 1);
    if (func_8002A28C() != 0) {
        if (temp_s0 >= 0) {
            D_80078EE8 += arg0;
            if (func_8002A200() != 0) {
                if (temp_s0 != 0) {
                    D_80078EE8 = func_8002A28C();
                    return 0;
                }
                func_8002A234();
                return 1;
            }
            goto block_6;
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return 0;
    }
block_6:
    return 0;
}
