/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D4FF4;
void func_80154274();
void func_80146994();
void func_80146CA0();
typedef struct {
    u8 pad[0x44];
    u32 flags;
    u8 pad48[0x234-0x48];
    s32 f234;
} T;
void func_8015E22C(T *p) {
    func_80154274(p, &D_800D4FF4);
    p->f234 = 0;
    func_80146994(5, p, 0xA, 0);
    p->flags |= 2;
    func_80146CA0(p);
}
