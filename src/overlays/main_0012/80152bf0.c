/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80062C14;
void func_80019064();
void func_80151204();
void func_80149020();
void func_80146CA0();
typedef struct { u8 pad_0[242]; s16 fF2; } T;
void func_80152BF0(T *p) {
    func_80019064(&D_80062C14);
    func_80151204(p, p->fF2);
    func_80149020(p);
    func_80146CA0(p);
}
