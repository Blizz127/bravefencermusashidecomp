/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D51E0;
extern s32 D_801806A0;
void func_80154274();
void func_80154A74();
void func_80146DB8();
void func_80146994();
void func_80147324();
void func_80146CA0();
typedef struct {
    u8 pad[0x1AA];
    u8 f1AA;
    u8 pad1AB[0x234-0x1AB];
    s32 f234;
} T;
void func_80158038(T *p) {
    p->f1AA = 0xE;
    func_80154274(p, &D_800D51E0);
    func_80154A74(p, 0x15);
    func_80146DB8(p, &D_801806A0);
    p->f234 = 0;
    func_80146994(5, p, 0xC, 0);
    func_80147324(0x455);
    func_80146CA0(p);
}
