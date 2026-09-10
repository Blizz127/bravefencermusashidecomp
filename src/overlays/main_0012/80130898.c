/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80130898 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): if arg0->unkB4 & 0x4000,
 * arg0->unkAA = 0x100 (v1 = 0x100 set in the branch delay slot)
 * and arg0->unk5C &= ~1. Then func_80131CA8(arg0, 0x28) (result
 * ignored). Returns void. */

struct obj_80130898 {
    u8 pad[0x5C];
    u16 unk5C;
    u8 pad2[0xAA - 0x5E];
    u16 unkAA;
    u8 pad3[0xB4 - 0xAC];
    s32 unkB4;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_80130898(struct obj_80130898 *arg0) {
    if (arg0->unkB4 & 0x4000) {
        arg0->unkAA = 0x100;
        arg0->unk5C &= ~1;
    }
    func_80131CA8(arg0, 0x28);
}
