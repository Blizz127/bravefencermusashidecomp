/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80019064();
void func_80151204();
void func_80149020();
void func_801472C8();
void func_80146DB8();
void func_801477E8();
void func_8014CBF8();
void func_801474EC();
void func_80146A6C();
void func_80147324();
void func_80146CA0();
extern s32 D_80062C04;
extern s32 D_801800B4;
typedef struct {
    u8 pad[6]; s16 a; u8 pad8[2]; s16 b; u8 padC[2]; s16 c;
    u8 pad10[0xCE]; u8 de;
    u8 padDF[0x13]; s16 uF2;
} T;
void func_801520DC(T *p) {
    func_80019064(&D_80062C04);
    func_80151204(p, p->uF2);
    func_80149020(p);
    func_801472C8(p);
    p->de = 0x10;
    func_80146DB8(p, &D_801800B4);
    func_801477E8(p, 0x40000);
    func_8014CBF8(p);
    func_801474EC(p);
    func_80146A6C(0x10, p, p->a, p->b, p->c, 0, 0);
    func_80147324(0x441);
    func_80146CA0(p);
}
