/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80165AC8();
typedef struct Inner { u8 pad[0x2C]; u16 f; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x20]; s32 flags;
    u8 pad48[0x197-0x48]; u8 unk197;
} T;
void func_80165A78(T *p) {
    func_80165AC8(p);
    p->unk197 = 0;
    p->flags &= ~8;
    p->inner->f &= ~0x20;
}
