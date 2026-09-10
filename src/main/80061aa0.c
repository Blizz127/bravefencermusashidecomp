/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_8005CE88(s32);                               /* static */
s32 func_8005CF08();                                /* static */
void func_8005CF18();                                  /* static */
extern s32 D_80078C3C;
extern s32 D_80078C40;
extern s32 D_80078C44;
extern s32 D_80078C48;
extern s32 D_80078C4C;
extern s32 D_80078C50;
extern s32 D_80078C54;
extern s32 D_80078C58;

void func_80061AA0(void) {
    s32 temp_s0;

    temp_s0 = func_8005CF08();
    func_8005CE88(D_80078C3C);
    func_8005CE88(D_80078C40);
    func_8005CE88(D_80078C44);
    func_8005CE88(D_80078C48);
    func_8005CE88(D_80078C4C);
    func_8005CE88(D_80078C50);
    func_8005CE88(D_80078C54);
    func_8005CE88(D_80078C58);
    if (temp_s0 == 1) {
        func_8005CF18();
    }
}
