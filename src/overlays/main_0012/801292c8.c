/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801292C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): loads word unk20;
 * when non-NULL calls func_80016714(unk20, tag == 1 ? 0x84 :
 * 0x38) (size chosen by the bne delay-slot pair); always zeroes
 * u16 unk0 (sh, shared exit). */

struct obj_801292C8 {
    u16 unk0;
    u8 pad[0x20 - 0x2];
    void *unk20;
};

extern void func_80016714(void *arg0, s32 arg1);

void func_801292C8(struct obj_801292C8 *arg0) {
    if (arg0->unk20 != 0) {
        func_80016714(arg0->unk20, *(u16 *) arg0->unk20 == 1 ? 0x84 : 0x38);
    }
    arg0->unk0 = 0;
}
