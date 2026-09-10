/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D5128;
extern s32 D_8018066C;
void func_80156648();
void func_80154274();
void func_80154A74();
void func_80147324();
void func_80146DB8();
void func_80146994();
void func_80146CA0();
void func_801725A4();
typedef struct { u8 pad[0x1AA]; u8 f1AA; } T;
void func_801578C0(T *p) {
    func_80156648(p);
    p->f1AA = 9;
    func_80154274(p, &D_800D5128);
    func_80154A74(p, 0x15);
    func_80147324(0xC20);
    func_80146DB8(p, &D_8018066C);
    func_80146994(4, p, 7, 0);
    func_80146994(5, p, 9, 0);
    func_80146CA0(p);
    func_801725A4(p);
}
