/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012CBF4();
void func_80131E00();
void func_801319E0();
void func_80131C78();
void func_80131CA8();
typedef struct { u8 pad[0x1C]; s32 u1C; u8 pad20[0x94]; s32 uB4; } T;
void func_8012FDA8(T *p) {
    s32 v;
    u8 lo;
    if (p->uB4 & 0x100) {
        p->u1C = p->u1C + 1;
        if (p->u1C >= 0x15) {
            func_80131E00(p, 0xD);
            return;
        }
        v = func_8012CBF4(p);
        if (v & 0x2000) {
            lo = (u8)v;
            if (lo == 2) {
                func_80131E00(p, 0x12);
                return;
            }
            if (lo == 0x1A) {
                func_801319E0(p);
                return;
            }
            func_80131C78(p);
        }
    }
    func_80131CA8(p, 0x1D);
}
