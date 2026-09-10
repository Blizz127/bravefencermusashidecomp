/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147AD4();
void func_801473EC();
s32 func_80161208();
void func_8016706C();
void func_80154274();
void func_80146CA0();
void func_80155FF8();
void func_801725A4();
extern s32 D_800D51AC;
typedef struct {
    u8 pad[0x2C]; s32 u2C;
    u8 pad30[0x14]; s32 flags;
    u8 pad48[0x162]; u8 u1AA;
} T;
void func_80157AC8(T *p) {
    p->flags |= 2;
    func_80147AD4(p, 0, 0, 0x10000);
    func_801473EC(p);
    if (func_80161208(p) == 0) {
        if (p->u2C > 0) {
            func_8016706C(4);
            func_8016706C(5);
            func_80154274(p, &D_800D51AC);
            func_80146CA0(p);
        } else {
            func_80155FF8(p, p->u1AA);
            func_801725A4(p);
        }
    }
}
