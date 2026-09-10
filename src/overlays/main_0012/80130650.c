/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801319E0();
s32 func_8012BEE8();
s32 func_8012CBF4();
s32 func_80131D68();
void func_80131C78();
void func_80131CA8();
typedef struct Inner { u8 pad[0x10]; s16 u10; } Inner;
typedef struct {
    u8 pad[0xA]; s16 uA;
    u8 padC[0x14]; Inner *inner;
    u8 pad24[0x90]; s32 uB4;
    u8 padB8[0xC]; s32 uC4;
} T;
void func_80130650(T *p) {
    s32 s1;
    if (p->uB4 & 0x1000) {
        if (p->uA >= 0x10) {
            func_801319E0(p);
            return;
        }
        if (func_8012BEE8(p)) {
            func_801319E0(p);
            return;
        }
        if (p->uC4 & 4) {
            p->inner->u10 -= 0x100;
        }
        s1 = func_8012CBF4(p);
        if (func_80131D68(p, s1) == 1) {
            return;
        }
        if (s1 & 0x2000) {
            func_80131C78(p);
        }
    }
    func_80131CA8(p, 0x23);
}
