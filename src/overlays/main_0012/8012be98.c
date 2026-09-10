/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BE98 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. NOTE: func_8004CFEC is declared (s32, s32) per
 * the func_8012B77C evidence. Fully grounded from raw asm: both stack triples force their middle half to 0 (sh zero at +0x12/+0x1A); all other halves are lhu loads. The 800132BC result is unused (void function); 800132BC is declared s32 because func_8012AF0C uses its result. */

struct src_8012BE98 {
    u8 pad[6];
    u16 unk6;
    u8 pad2[6];
    u16 unkE;
};

struct triple_8012BE98 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

extern s32 func_800132BC(u16 *arg0, u16 *arg1);

void func_8012BE98(struct src_8012BE98 *arg0, struct triple_8012BE98 *arg1) {
    u16 t1[3];
    u16 t2[3];

    t1[0] = arg0->unk6;
    t1[1] = 0;
    t1[2] = arg0->unkE;
    t2[0] = arg1->unk0;
    t2[1] = 0;
    t2[2] = arg1->unk4;
    func_800132BC(t1, t2);
}

