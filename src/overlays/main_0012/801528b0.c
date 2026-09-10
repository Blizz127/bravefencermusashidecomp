/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80062C04;
extern s32 D_800D5880;
extern s32 D_801800FC;
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
typedef struct { u8 pad[0xDE]; u8 fDE; u8 padDF[0xF2-0xDF]; s16 fF2; } T;
void func_801528B0(T *p) {
    func_80019064(&D_80062C04);
    func_80151204(p, p->fF2);
    func_80149020(p);
    func_80154274(p, &D_800D5880);
    func_80147324(0x451);
    p->fDE = 0x10;
    func_80146DB8(p, &D_801800FC);
    func_801477E8(p, 0xFFF00000);
    func_8014CBF8(p);
    func_801474EC(p);
    func_80146CA0(p);
}
