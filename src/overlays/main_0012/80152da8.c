/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80019064();
void func_80151204();
void func_80149020();
void func_80154274();
void func_80147324();
void func_80146DB8();
void func_801477E8();
void func_8014CBF8();
void func_801474EC();
void func_80146CA0();
extern s32 D_80062C14;
extern s32 D_800D5880;
extern s32 D_8018012C;
typedef struct { u8 pad[0xDE]; u8 de, df; u8 padE0[0x12]; s16 uF2; } T;
void func_80152DA8(T *p) {
    func_80019064(&D_80062C14);
    func_80151204(p, p->uF2);
    func_80149020(p);
    func_80154274(p, &D_800D5880);
    func_80147324(0x451);
    p->de = 0x10;
    p->df = 8;
    func_80146DB8(p, &D_8018012C);
    func_801477E8(p, 0xFFE40000);
    func_8014CBF8(p);
    func_801474EC(p);
    func_80146CA0(p);
}
