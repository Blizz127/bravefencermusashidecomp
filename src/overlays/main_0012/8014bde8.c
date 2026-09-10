/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8016F1AC();
s32 func_8017267C();
void func_80015978();
s32 func_80013294();
void func_80029ED4();
typedef struct { u8 b[8]; } S;
typedef struct { u8 pad[0x98]; S u98; } T;
void func_8014BDE8(T *p) {
    S tmp;
    s16 vec[4];
    if (func_8016F1AC()) {
        return;
    }
    if (func_8017267C(p)) {
        return;
    }
    tmp = p->u98;
    func_80015978((u8 *)p + 4, vec);
    vec[1] = 0;
    ((s16 *)&tmp)[1] = 0;
    func_80029ED4((s16)func_80013294(&tmp, vec));
}
