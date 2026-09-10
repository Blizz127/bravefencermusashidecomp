/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F828 (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): unconditionally sets byte
 * unkC1 = 4 (sb in the beqz delay slot); when word unkB4 & 8
 * calls 80131170(obj, &D_8017E6F0, 0xB) (a0 still holds obj at
 * the jal: pass-through first arg, m2c showed two); ends with
 * 31CA8(obj, 9). */

struct obj_8012F828 {
    u8 pad[0xB4];
    s32 unkB4;
    u8 pad2[0xC1 - 0xB8];
    u8 unkC1;
};

extern u8 D_8017E6F0;
extern void func_80131170(void *arg0, void *arg1, s32 arg2);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F828(struct obj_8012F828 *arg0) {
    arg0->unkC1 = 4;
    if (arg0->unkB4 & 8) {
        func_80131170(arg0, &D_8017E6F0, 0xB);
    }
    func_80131CA8(arg0, 9);
}
