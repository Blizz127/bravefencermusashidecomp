/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012B14C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Raw: a0 = *(arg0+0x20)+0x34 (byte offset, delay slot), a2 = arg0+0x10; a1 is never set, so the call passes an indeterminate second argument (a pointer-sized slot; the sibling func_8012B178 passes a buffer address there) (minimal frame leaves no local slot; documented as-is). */

struct obj_8012B14C {
    u8 pad[0x20];
    u8 *unk20;
};

void func_800484EC(u8 *arg0, s32 *arg1, void *arg2);

void func_8012B14C(struct obj_8012B14C *arg0) {
    s32 *trash;

    func_800484EC(arg0->unk20 + 0x34, trash, (u8 *) arg0 + 0x10);
}

