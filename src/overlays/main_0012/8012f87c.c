/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F87C (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): when word unkB4 & 8 calls
 * 80131340(obj) (a0 still holds obj at the jal with a nop delay
 * slot: pass-through arg, m2c showed none); ends with
 * 31CA8(obj, 0xA). */

struct obj_8012F87C {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_80131340(void *arg0);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F87C(struct obj_8012F87C *arg0) {
    if (arg0->unkB4 & 8) {
        func_80131340(arg0);
    }
    func_80131CA8(arg0, 0xA);
}
