/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
extern S D_80126B30;
void func_80172CA0();
void func_80174684();
void func_80172C50(S *p) {
    D_80126B30 = *p;
    func_80174684(func_80172CA0);
}
