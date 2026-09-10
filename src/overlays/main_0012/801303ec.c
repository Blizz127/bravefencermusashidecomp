/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801303EC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): if s0->unkB4 & 0x10,
 * func_801319E0(s0, arg1) (a0 = s0 live, a1 passes through
 * untouched; nop delay slot). Then func_80131CA8(s0, 0xC)
 * (result ignored). Returns void. */

struct obj_801303EC {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_801319E0(void *arg0, s32 arg1);
extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_801303EC(struct obj_801303EC *arg0, s32 arg1) {
    if (arg0->unkB4 & 0x10) {
        func_801319E0(arg0, arg1);
    }
    func_80131CA8(arg0, 0xC);
}
