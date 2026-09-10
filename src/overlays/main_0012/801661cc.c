/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801661CC (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk20/unk10/unk18 on a void*, plus arg0 + 0x24
 * passed as an address. The disassembly loads/stores the members as
 * words (lw +0x20/+0x10/+0x18, sw +0x10/+0x18) and computes the
 * address with a byte addiu ($a1, $s0, 0x24), so the model declares
 * three s32 members and spells the address with a (u8 *) cast — the
 * same addiu either way. Callee declarations follow the repo pipeline
 * convention. Body is m2c's verbatim. */

struct data_801661CC {
    u8 pad[0x10];
    s32 unk10;
    u8 pad2[0x4];
    s32 unk18;
    u8 pad3[0x4];
    s32 unk20;
};

s32 func_80128ED8(s32, void *);
void func_80146C3C(void *);
void func_800D22E4();

void func_801661CC(struct data_801661CC *arg0) {
    s32 temp_a0;
    s32 temp_v0;

    if (func_80128ED8(arg0->unk20, (void *) ((u8 *) arg0 + 0x24)) != 0) {
        func_80146C3C(arg0);
        return;
    }
    func_800D22E4(arg0);
    temp_v0 = arg0->unk10;
    temp_a0 = arg0->unk18;
    arg0->unk10 = (s32) ((temp_v0 >> 1) + (temp_v0 >> 2));
    arg0->unk18 = (s32) ((temp_a0 >> 1) + (temp_a0 >> 2));
}
