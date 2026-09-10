/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80015978();
s32 func_80133784();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
} T;
void func_801483E8(T *p) {
    s16 a[4];
    s16 b[4];
    func_80015978((u8 *)p + 4, a);
    b[0] = a[0];
    b[1] = a[1] + 8;
    b[2] = a[2];
    if (func_80133784(1, a, b) != 0x2000) {
        return;
    }
    if (p->u6 != b[0] || p->uA != b[1] || p->uE != b[2]) {
        return;
    }
    if (((u8 *)b)[6]) {
        return;
    }
    func_80015978((u8 *)p + 4, (u8 *)p + 0xA0);
}
