/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BC60 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Loads grounded as lh (s16 triple-diffs); the two call arguments are the same stack base (addu in raw). Callee result unused, so void return. */

extern void func_80049324(s32 *arg0, s32 *arg1);

struct pt_8012BC60 {
    u8 pad[2];
    s16 unk2;
    u8 pad2[2];
    s16 unk6;
    u8 pad3[2];
    s16 unkA;
};

s32 func_8012BC60(struct pt_8012BC60 *arg0, struct pt_8012BC60 *arg1) {
    s32 sp[3];

    sp[0] = arg0->unk2 - arg1->unk2;
    sp[1] = arg0->unk6 - arg1->unk6;
    sp[2] = arg0->unkA - arg1->unkA;
    func_80049324(sp, sp);
    return sp[0] + sp[1] + sp[2];
}

