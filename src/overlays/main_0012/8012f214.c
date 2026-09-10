/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F214 (main_0012.s), decoded manually from
 * raw asm (0x60 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): t = unk20 + 0x34;
 * calls 8004914C(t) (t set in the jal delay slot), 800491AC(t),
 * then 8004945C(arg1, arg2, buf) with an 8-byte stack buffer.
 * Same tail shape as func_8012F14C with the GTE-base override. */

struct obj_8012F214 {
    u8 pad[0x20];
    void *unk20;
};

extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern void func_8004945C(void *arg0, void *arg1, void *arg2);

void func_8012F214(struct obj_8012F214 *arg0, void *arg1, void *arg2) {
    u8 *t;
    u8 buf[8];

    t = (u8 *) arg0->unk20 + 0x34;
    func_8004914C(t);
    func_800491AC(t);
    func_8004945C(arg1, arg2, buf);
}
