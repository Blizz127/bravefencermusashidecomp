/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s32 w[8]; } M_80017E8C;
extern s32 D_800AF648;
void func_8004838C();
void func_8004914C();
void func_800491AC();
void func_80017E8C(M_80017E8C *src) {
    M_80017E8C tmp = *src;
    func_8004838C(&D_800AF648, &tmp, &tmp);
    func_8004914C(&tmp);
    func_800491AC(&tmp);
}
