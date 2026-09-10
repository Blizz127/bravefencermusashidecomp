/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80136BC4();
extern void *D_80184124[];
extern void *D_80184120;
void func_8013373C(s32 a0) {
    void *p = D_80184124[(s16)a0];
    if (p) {
        D_80184120 = p;
        func_80136BC4(p);
    }
}
