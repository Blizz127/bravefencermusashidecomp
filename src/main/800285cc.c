/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80053978();
void func_800538EC();
typedef struct { s16 a; u8 pad2[2]; s32 b; u8 c; u8 pad9; u8 d; } S;
extern S D_800C6D18;
void func_800285CC(void) {
    D_800C6D18.a = -0x106;
    D_800C6D18.b = 0x1F40000;
    D_800C6D18.c = 0;
    D_800C6D18.d = 0;
    func_80053978(&D_800C6D18);
    func_800538EC(1);
}
