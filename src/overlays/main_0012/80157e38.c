/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D4F14;
void func_80154274();
void func_80154A74();
void func_80146994();
void func_80147324();
void func_80146CA0();
typedef struct {
    u8 pad[0x1AA];
    u8 f1AA;
    u8 pad1AB[0x244-0x1AB];
    s16 f244;
} T;
void func_80157E38(T *p) {
    p->f1AA = 0xD;
    func_80154274(p, &D_800D4F14);
    func_80154A74(p, 0x15);
    func_80146994(5, p, 0, 0);
    func_80147324(0x455);
    p->f244 = 0;
    func_80146CA0(p);
}
