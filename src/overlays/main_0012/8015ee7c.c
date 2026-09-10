/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D4C48;
extern s32 D_80180A00;
void func_8014CBF8();
void func_801474EC();
void func_80154274();
void func_80146DB8();
void func_801477E8();
void func_80146CA0();
void func_8015EE7C(void *p) {
    func_8014CBF8(p);
    func_801474EC(p);
    func_80154274(p, &D_800D4C48);
    func_80146DB8(p, &D_80180A00);
    func_801477E8(p, 0xFFF40000);
    func_80146CA0(p);
}
