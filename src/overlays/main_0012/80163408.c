/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
extern S D_8018393C;
void func_8016345C();
void func_80163408(s32 a0, s32 a1, s32 a2, s32 a3) {
    S tmp;
    tmp = D_8018393C;
    func_8016345C(a0, a1 & 0xFFFF, a2, a3 & 0xFFFF, &tmp);
}
