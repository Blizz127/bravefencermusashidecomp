/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801599A4();
void func_80159B3C();
s32 func_80157F64();
void func_80155FF8();
s16 *func_80156600();
void func_80146A6C();
typedef struct {
    u8 pad[0x44]; s32 flags;
    u8 pad48[0x70]; u16 b8;
    u8 padBA[0xF0]; u8 u1AA;
    u8 pad1AB[0x99]; s16 u244;
} T;
void func_80157EA4(T *p) {
    s16 *v;
    p->flags |= 2;
    if (p->b8 == 0x8000) {
        func_801599A4(p);
        func_80159B3C(p);
        return;
    }
    if (func_80157F64(p)) {
        return;
    }
    func_80155FF8(p, p->u1AA);
    v = func_80156600(p);
    if (v == 0) {
        return;
    }
    if (p->u244) {
        return;
    }
    p->u244 = 1;
    func_80146A6C(0x54, p, v[0], v[1], v[2], 0, 0);
}
