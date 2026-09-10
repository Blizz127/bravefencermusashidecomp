/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014F468();
void func_8014F6F4();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[0x34]; s32 flags;
    u8 pad48[0x40]; s16 u88, u8A, u8C;
} T;
s32 func_8014F3E8(T *p) {
    if (p->flags & 0x40000) {
        return 0;
    }
    if (p->u6 == p->u88 && p->uA == p->u8A && p->uE == p->u8C) {
        func_8014F468();
        return;
    }
    func_8014F6F4();
}
