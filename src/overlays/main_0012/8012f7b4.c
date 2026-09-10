/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F7B4 (main_0012.s), decoded manually from
 * raw asm (0x74 bytes; m2c BEE8() misread corrected: the jal has
 * a nop delay slot with a0 still holding obj, so it is
 * BEE8(arg0) by pass-through; NOT verified against retail;
 * C89-gated only, promotion requires an oracle MATCH): when word
 * unkB4 & 4, calls BEE8(obj); when word unk1C is 1 and
 * 31A34(obj, 8) returns 0, calls 31A34(obj, 0x20). Always ends
 * with 31CA8(obj, 7). */

struct obj_8012F7B4 {
    u8 pad[0x1C];
    s32 unk1C;
    u8 pad2[0xB4 - 0x20];
    s32 unkB4;
};

extern s32 func_8012BEE8(void *arg0);
extern s32 func_80131A34(void *arg0, s32 arg1);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F7B4(struct obj_8012F7B4 *arg0) {
    if (arg0->unkB4 & 4) {
        func_8012BEE8(arg0);
        if (arg0->unk1C == 1 && func_80131A34(arg0, 8) == 0) {
            func_80131A34(arg0, 0x20);
        }
    }
    func_80131CA8(arg0, 7);
}
