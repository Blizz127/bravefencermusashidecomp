/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014E934();
void func_8014CC28();
void func_8014F3E8();
void func_80151DB0();
void func_80146CA0();
typedef struct {
    u8 pad_0[222];
    u8 fDE;
} T;
void func_80151D60(T *p) {
    func_8014E934(p);
    func_8014CC28(p);
    func_8014F3E8(p);
    func_80151DB0(p);
    p->fDE = 32;
    func_80146CA0(p);
}
