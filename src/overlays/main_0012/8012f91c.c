/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F91C (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): F87C-sibling: when word
 * unkB4 & 0x80 calls 80131340(obj) (pass-through a0, nop delay
 * slot); ends with 31CA8(obj, 0x17). */

struct obj_8012F91C {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_80131340(void *arg0);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F91C(struct obj_8012F91C *arg0) {
    if (arg0->unkB4 & 0x80) {
        func_80131340(arg0);
    }
    func_80131CA8(arg0, 0x17);
}
