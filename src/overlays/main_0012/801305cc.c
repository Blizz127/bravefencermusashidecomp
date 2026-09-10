/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80131A34();
void func_80131CA8();
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    u8 pad20[0x78]; s16 u98;
    u8 pad9A[0x1A]; s32 uB4;
    u8 padB8[9]; u8 uC1;
    u8 padC2[2]; s32 uC4;
} T;
void func_801305CC(T *p) {
    p->uC1 = 0xC;
    if (p->uB4 & 0x1000) {
        p->u1C = 0x3C;
        p->uC4 &= -5;
        if (func_80131A34(p, 0x20)) {
            p->uC4 |= 4;
        } else {
            p->u98 = 0;
        }
    }
    func_80131CA8(p, 0x22);
}
