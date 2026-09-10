/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8017BFF8();
s32 func_80028FBC();
s32 func_80029000();
s32 func_80028D9C();
void func_8002D4C8();
void func_80145934();
void func_800D1D24();
extern s16 D_801853F2;
void func_8017BF70(void) {
    s32 v = func_8017BFF8();
    D_801853F2 = v;
    if ((s16)v >= 0) {
        return;
    }
    func_8002D4C8(0x21, func_80028FBC() & 0xFFFF);
    func_8002D4C8(0x22, func_80029000() & 0xFFFF);
    if (func_80028D9C() == 0) {
        func_8002D4C8(0xC, 0);
    } else {
        func_8002D4C8(0xB, 0);
    }
    func_80145934();
    func_800D1D24();
}
