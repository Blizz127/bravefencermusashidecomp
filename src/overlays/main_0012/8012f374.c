/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F374 (main_0012.s), decoded manually from
 * raw asm (0x98 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): F2E8-family with
 * global seeds: builds an s32 triple of s16 {D_80126CB4,
 * D_80126CB6, D_80126CB8} (lh) minus target words +0x48/+0x4C/
 * +0x50 (lw/subu), runs func_8004D504(unk20 + 0x34, in, out)
 * (a0 = unk20 + 0x34 in the jal delay slot), and stores the three
 * result words as halfwords to out[0/2/4] (lw/sh). */

struct obj_8012F374 {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012F374 {
    u8 pad[0x48];
    s32 unk48;
    s32 unk4C;
    s32 unk50;
};

struct out_8012F374 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern s16 D_80126CB4;
extern s16 D_80126CB6;
extern s16 D_80126CB8;
extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F374(struct obj_8012F374 *arg0, struct out_8012F374 *arg1) {
    struct tgt_8012F374 *t;
    s32 in[3];
    s32 out[3];

    t = (struct tgt_8012F374 *) arg0->unk20;
    in[0] = D_80126CB4 - t->unk48;
    in[1] = D_80126CB6 - t->unk4C;
    in[2] = D_80126CB8 - t->unk50;
    func_8004D504((u8 *) t + 0x34, in, out);
    arg1->unk0 = (s16) out[0];
    arg1->unk2 = (s16) out[1];
    arg1->unk4 = (s16) out[2];
}
