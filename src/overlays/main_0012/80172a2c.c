/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80126B30;
void func_80147060();
void func_80149350();
void func_80171A1C();
void func_80172A8C();
typedef struct {
    u8 pad[0x20];
    u8 *inner;
    u8 pad24[0x132-0x24];
    u16 f132;
    u8 pad134[2];
    s16 f136;
} T;
void func_80172A2C(T *p) {
    func_80147060(p);
    p->f136 = 2;
    p->f132 = *(u16 *)(p->inner + 0x12);
    func_80149350(p, &D_80126B30, &D_80126B30);
    func_80171A1C(p);
    func_80172A8C(p);
}
