/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F2E8 (main_0012.s), decoded manually from
 * raw asm (0x8C bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): F038-variant keyed
 * off the target words: builds an s32 triple of (s16)arg1[0/2/4]
 * minus target words +0x48/+0x4C/+0x50 (lh/lw/subu), runs
 * func_8004D504(unk20 + 0x34, in, out) (a0 = unk20 + 0x34 in the
 * jal delay slot; 8004D504 writes results through a2), and
 * stores the three result words as halfwords to out[0/2/4]. */

struct obj_8012F2E8 {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012F2E8 {
    u8 pad[0x48];
    s32 unk48;
    s32 unk4C;
    s32 unk50;
};

struct u16in_8012F2E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

struct out_8012F2E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F2E8(struct obj_8012F2E8 *arg0, struct u16in_8012F2E8 *arg1, struct out_8012F2E8 *arg2) {
    struct tgt_8012F2E8 *t;
    s32 in[3];
    s32 out[3];

    t = (struct tgt_8012F2E8 *) arg0->unk20;
    in[0] = arg1->unk0 - t->unk48;
    in[1] = arg1->unk2 - t->unk4C;
    in[2] = arg1->unk4 - t->unk50;
    func_8004D504((u8 *) t + 0x34, in, out);
    arg2->unk0 = (s16) out[0];
    arg2->unk2 = (s16) out[1];
    arg2->unk4 = (s16) out[2];
}
