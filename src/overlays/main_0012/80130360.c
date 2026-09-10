/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80131CA8();
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    u8 pad20[0x3C]; s16 u5C;
    u8 pad5E[0x3A]; s16 u98;
    u8 pad9A[0x1A]; s32 uB4;
    u8 padB8[9]; u8 uC1;
} T;
void func_80130360(T *p) {
    p->uC1 = 2;
    if (p->uB4 & 2) {
        p->u5C = 0;
        p->u98 = 0;
        p->u1C = 0;
    }
    func_80131CA8(p, 1);
}
