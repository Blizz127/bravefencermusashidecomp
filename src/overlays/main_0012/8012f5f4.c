/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80131B14();
void func_80131E00();
s32 func_80131A34();
void func_80131CA8();
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    u8 pad20[0x56]; s16 u76;
    u8 pad78[0x20]; s16 u98;
    u8 pad9A[0x27]; u8 uC1, uC2;
    u8 padC3; s32 uC4;
} T;
void func_8012F5F4(T *p) {
    p->uC1 = 1;
    if (p->uC4 & 2) {
        func_80131CA8(p, 3);
        return;
    }
    func_80131B14(p);
    if (p->u76 <= 0) {
        func_80131E00(p, 0xC);
        return;
    }
    if (func_80131A34(p, 4)) {
        p->uC2 = 0;
    } else {
        p->u98 = 0;
        p->uC2 = 1;
        p->u1C = 0x10;
    }
    func_80131CA8(p, 3);
}
