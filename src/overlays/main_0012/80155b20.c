/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80161208();
void func_80146D80();
void func_801477E8();
void func_80154274();
void func_80146CA0();
extern s32 D_800D4DA8;
typedef struct { u8 pad[0x44]; s32 flags; u8 pad48[0x70]; u16 f; } T;
void func_80155B20(T *p) {
    p->flags |= 2;
    if (func_80161208(p) == 0 && p->f == 0x8000) {
        func_80146D80(p);
        func_801477E8(p, 0xFFF00000);
        func_80154274(p, &D_800D4DA8);
        func_80146CA0(p);
    }
}
