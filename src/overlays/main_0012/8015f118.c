/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80147078();
void func_80159B70();
void func_8014AB5C();
void func_801466F0();
void func_80019064();
void func_80147324();
s32 func_80161208();
void func_80155FF8();
extern s32 D_80062BE8;
typedef struct {
    u16 idx;
    u8 pad2[0x42]; s32 flags;
    u8 pad48[0x70]; u16 b8;
    u8 padBA[0xF0]; u8 u1AA;
} T;
void func_8015F118(T *p) {
    p->flags |= 2;
    if (p->b8 == 0x8000) {
        D_80180A1C[p->idx](p);
        func_80147078(p, 0);
        func_80159B70(p);
        return;
    }
    if (p->b8 & 0x4000) {
        func_8014AB5C(0x19);
        func_8014AB5C(0x1D);
        func_801466F0(0x19, p, 0, 0, 0, 0, 0, 1);
        func_801466F0(0x19, p, 0, 0, 0, 1, 0, 1);
        func_801466F0(0x1D, p, 0, 0, 0, 0, 0, 1);
        func_80019064(&D_80062BE8);
        func_80147324(0x9DA);
    }
    if (func_80161208(p) == 0) {
        func_80155FF8(p, p->u1AA);
    }
}
