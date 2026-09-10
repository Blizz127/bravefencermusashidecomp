/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80161208();
s32 func_8014A850();
void func_80154274();
void func_8015E40C();
void func_8015E588();
void func_8015E4B0();
void func_80146994();
void func_80146CA0();
void func_80146C98();
extern s32 D_800D5098;
extern s32 D_800D5060;
typedef struct { u8 pad[0xB8]; u16 uB8; } T;
void func_8015E288(T *p) {
    if (func_80161208(p)) {
        return;
    }
    if (func_8014A850(p)) {
        func_80154274(p, &D_800D5098);
        func_8015E40C(p);
        func_8015E588(p);
        func_8015E4B0(p);
        func_80146994(5, p, 0xB, 0);
        func_80146CA0(p);
    } else if (p->uB8 & 0x8000) {
        func_80154274(p, &D_800D5060);
        func_80146C98(p, 3);
    }
}
