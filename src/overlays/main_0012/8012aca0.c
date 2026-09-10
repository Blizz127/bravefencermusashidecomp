/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012ACA0 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Fully grounded from raw asm: unk90 gets the full lui+addiu address of the data word D_8017E6AC (which itself holds 0x80063548); sw/sw/sw/sh at 0x90/0x94/0x9C/0x9A; lhu+andi+sh at 0x72. */

extern s32 D_8017E6AC;

struct obj_8012ACA0 {
    u8 pad[0x72];
    u16 unk72;
    u8 pad2[0x1C];
    void *unk90;
    s32 unk94;
    s16 unk98;
    s16 unk9A;
    s32 unk9C;
};

void func_8012AAAC(void);

void func_8012ACA0(struct obj_8012ACA0 *arg0) {
    arg0->unk90 = &D_8017E6AC;
    arg0->unk94 = 0;
    arg0->unk9C = 0;
    arg0->unk9A = 0;
    arg0->unk72 &= 0xF9FF;
    func_8012AAAC();
}

