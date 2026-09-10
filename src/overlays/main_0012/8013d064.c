#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801841B0;
extern s32 D_801841BC;
extern s32 D_801841C8;
extern s32 D_801841CC;
void func_8013D9B0();                                 /* static */

void func_8013D064(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    if (D_801841C8 != 0) {
        if (D_801841C8 != 2) {
            if ((D_801841C8 < 3) && (D_801841C8 == 1)) {
                temp_v0 = D_801841CC + 1;
                D_801841CC = temp_v0;
                if (temp_v0 >= 0x23B) {
                    D_801841B0 = (s32) D_801841C8;
                    D_801841C8 = 2;
                }
            }
        } else {
            temp_v0_2 = D_801841B0 - 1;
            D_801841B0 = temp_v0_2;
            if (temp_v0_2 == 0) {
                D_801841B0 = (s32) D_801841C8;
                func_8013D9B0(2);
                if (D_801841BC == 0) {
                    D_801841C8 = (s32) (D_801841C8 + 1);
                }
            }
        }
    }
}
