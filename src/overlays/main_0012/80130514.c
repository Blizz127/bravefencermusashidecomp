/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012CBF4();
void func_801319E0();
s32 func_80131D68();
s32 func_8012BEE8();
void func_80131CA8();
typedef struct {
    u8 pad[0xA]; s16 uA;
    u8 padC[0x52]; s16 u5E;
    u8 pad60[0x54]; s32 uB4;
    u8 padB8[9]; u8 uC1;
} T;
void func_80130514(T *p) {
    s32 s1;
    if (p->uB4 & 0x40) {
        s1 = func_8012CBF4(p);
        if (p->uA >= 0x10) {
            func_801319E0(p);
            return;
        }
        if (func_80131D68(p, s1) == 1) {
            return;
        }
        if (func_8012BEE8(p) && (s1 & 0x2000)) {
            p->uC1 = 0;
            p->u5E = 0;
            func_80131CA8(p, 0xE);
        }
    }
    func_80131CA8(p, 0x13);
}
