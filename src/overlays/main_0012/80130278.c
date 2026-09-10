/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80131170();
s32 func_80131CA8();
void func_80131E00();
typedef struct {
    u8 pad[0xB4]; s32 uB4;
    u8 padB8[9]; u8 uC1;
    u8 padC2[2]; s32 uC4;
} T;
void func_80130278(T *p) {
    s32 s1 = 0;
    p->uC1 = 0xB;
    if (p->uC4 & 1) {
        func_80131E00(p, 0xE);
        return;
    }
    if (p->uB4 & 0x800) {
        func_80131170(p, 0, 0);
        s1 = 1;
    }
    if (func_80131CA8(p, 0x2C)) {
        s1 = 1;
    }
    if (s1 == 0) {
        func_80131E00(p, 6);
    }
}
