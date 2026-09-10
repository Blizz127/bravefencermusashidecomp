/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801553A8();
void func_80154A74();
void func_80149048();
typedef struct {
    u8 pad[0x44];
    u32 flags;
    u8 pad48[0xF6-0x48];
    s16 fF6;
} T;
void func_8015F260(T *p) {
    func_801553A8(p);
    func_80154A74(p, 0x11);
    p->flags &= -3;
    p->flags &= -2;
    func_80149048(p);
    p->fF6 = 0x1000;
}
