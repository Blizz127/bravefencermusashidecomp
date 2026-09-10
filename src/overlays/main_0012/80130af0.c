/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146A6C();
void func_80131B14();
void func_80131E00();
s32 func_80131A34();
void func_80131CA8();
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    u8 pad20[0x56]; s16 u76;
    u8 pad78[4]; s16 u7C, u7E, u80;
    u8 pad82[0x16]; s16 u98;
    u8 pad9A[0x1A]; s32 uB4;
    u8 padB8[9]; u8 uC1, uC2;
    u8 padC3; s32 uC4;
} T;
void func_80130AF0(T *p) {
    p->uC1 = 0x13;
    if (p->uC4 & 2) {
        func_80131CA8(p, 3);
        return;
    }
    if (p->uB4 & 0x20000) {
        func_80146A6C(3, p, p->u7C, p->u7E, p->u80, 0xC0CFFF8, 0xF000B000);
        if ((p->uB4 & 1) || (p->uC4 & 2) == 0) {
            func_80131B14(p);
            if (p->u76 <= 0) {
                func_80131E00(p, 0xC);
                return;
            }
            if (func_80131A34(p, 4)) {
                p->uC2 = 0;
            } else {
                p->uC2 = 1;
                p->u98 = 0;
                p->u1C = 0x10;
            }
        }
        func_80131CA8(p, 3);
    }
    func_80131CA8(p, 0x37);
}
