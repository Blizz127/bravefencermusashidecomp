/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801553C0();
void func_80154A74();
typedef struct Inner { u8 pad[0x10]; s16 unk10; } Inner;
typedef struct {
    u8 pad[0x20];
    Inner *inner;
    u8 pad24[0x20];
    u32 flags;
    u8 pad48[0x1AC-0x48];
    s32 f1AC;
} T;
void func_80160DEC(T *p) {
    p->f1AC = 0;
    p->inner->unk10 = 0;
    func_801553C0(p);
    p->flags &= -0x181;
    func_80154A74(p, 0x11);
}
