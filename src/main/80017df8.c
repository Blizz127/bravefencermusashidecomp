/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8004978C();
void func_80048EAC();
typedef struct { s32 v[8]; } Tmp;
void func_80017DF8(void *a0, void *a1) {
    Tmp tmp;
    func_8004978C(a0, &tmp);
    func_80048EAC(&tmp, a1);
}
