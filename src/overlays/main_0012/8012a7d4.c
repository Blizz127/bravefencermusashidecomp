/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A7D4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Widths grounded from raw asm: six lw loads from the pointer block, six sh stores into the two out structs. */

struct src_8012A7D4 {
    u8 pad[0x3C];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
};

struct pair_8012A7D4 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern struct src_8012A7D4 *D_801151D4;

void func_8012A7D4(struct pair_8012A7D4 *arg0, struct pair_8012A7D4 *arg1) {
    arg0->unk0 = D_801151D4->unk3C;
    arg0->unk2 = D_801151D4->unk40;
    arg0->unk4 = D_801151D4->unk44;
    arg1->unk0 = D_801151D4->unk48;
    arg1->unk2 = D_801151D4->unk4C;
    arg1->unk4 = D_801151D4->unk50;
}

