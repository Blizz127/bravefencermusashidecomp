/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801549F8();
void func_80154418();
typedef struct {
    u8 pad[0xB4]; s32 fB4; s16 fB8, fBA; u8 fBC, fBD;
    u8 padBE[0x1E]; u8 fDC;
} T;
void func_8015430C(T *p, s32 a1, s32 a2) {
    p->fB4 = a1;
    p->fBA = 1;
    p->fB8 = 1;
    p->fBC = a2;
    p->fBD = a2;
    p->fDC = func_801549F8(p);
    func_80154418(p);
}
