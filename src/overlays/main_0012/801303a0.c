/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801303A0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): if s0->unkB4 & 2,
 * func_8012E364(s0) (a0 still holds s0; nop delay slot). Then
 * func_80131CA8(s0, 2) (result ignored). Returns void. */

struct obj_801303A0 {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_8012E364(void *arg0);
extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_801303A0(struct obj_801303A0 *arg0) {
    if (arg0->unkB4 & 2) {
        func_8012E364(arg0);
    }
    func_80131CA8(arg0, 2);
}
