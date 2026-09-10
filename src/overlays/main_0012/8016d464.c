/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800D22E4();
void func_8016CF04();
typedef struct { u8 pad[2]; u16 u2; u8 pad4[0x18]; s32 u1C; u8 pad20[0x14]; u16 *u34; } T;
void func_8016D464(T *p) {
    u16 *s1 = p->u34;
    func_800D22E4(p);
    func_8016CF04(p, 1);
    p->u1C = p->u1C - 1;
    if (p->u1C == -1 || s1[0] != 1) {
        p->u2 = p->u2 + 1;
    }
}
