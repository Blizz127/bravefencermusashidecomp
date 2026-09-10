/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80019064();
void func_80151204();
s32 func_80012A60();
void func_80154274();
void func_80149020();
void func_80147324();
void func_80146CA0();
void func_80172630();
extern s32 D_80062C14;
extern s32 D_800D5880;
extern s32 D_800D58AC;
typedef struct Inner { u8 pad[0x10]; s16 u10, u12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x40]; s16 u64;
    u8 pad66[0x8C]; s16 uF2, uF4;
} T;
void func_80151DB0(T *p) {
    s32 v;
    Inner *q;
    func_80019064(&D_80062C14);
    func_80151204(p, p->uF2);
    q = p->inner;
    v = func_80012A60(q->u12, p->uF4);
    if ((s16)v >= 0x401) {
        func_80154274(p, &D_800D5880);
        p->inner->u10 = 0xC00;
    } else {
        func_80154274(p, &D_800D58AC);
        p->inner->u10 = 0x400;
    }
    p->u64 = 0xCC;
    func_80149020(p);
    func_80147324(0x436);
    func_80146CA0(p);
    func_80172630(p);
}
