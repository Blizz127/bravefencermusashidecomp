/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
s32 func_801487F4();
void func_80160A74();
void func_80161208();
typedef struct { u16 idx; } T;
void func_801609B8(T *p) {
    if ((func_801487F4(p) & 8) == 0) {
        D_80180A1C[p->idx](p);
        func_80160A74(p);
    } else {
        func_80161208(p);
    }
}
