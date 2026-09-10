/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149020();
void func_80151C54();
void func_80159B3C();
void func_801542DC();
void func_8014E934();
s32 func_8014F3E8();
s32 func_8014CC28();
void func_8015BDD0();
void func_80165718();
extern s32 D_800D5880;
extern s32 D_800D46E4;
typedef struct {
    u8 pad[0xB4]; s32 uB4;
    u16 b8;
} T;
void func_80151AE4(T *p) {
    func_80149020(p);
    if (p->b8 == 0x8000) {
        func_80151C54(p);
        func_80159B3C(p);
        if (p->uB4 == (s32)&D_800D5880) {
            func_801542DC(p, &D_800D46E4, 0xE);
        }
        func_80165718(p);
        return;
    }
    func_8014E934(p);
    if (func_8014F3E8(p) || func_8014CC28(p)) {
        return;
    }
    func_80151C54(p);
    func_8015BDD0(p);
    func_80165718(p);
}
