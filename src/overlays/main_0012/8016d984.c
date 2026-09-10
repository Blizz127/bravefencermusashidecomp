/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8016D984 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk1C/unk10/unk14/unk18 on a void*. The disassembly
 * accesses all four as words (lw/sw at +0x10/+0x14/+0x18/+0x1C), so the
 * model declares exactly those four s32 members. Bytes below +0x10 are
 * untouched by this function and left as padding; no other layout is
 * guessed. Control flow and temporaries are m2c's verbatim. */

struct data_8016D984 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

void func_80146C3C();
void func_800D22E4(void *);

void func_8016D984(struct data_8016D984 *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    temp_v0 = arg0->unk1C - 1;
    arg0->unk1C = temp_v0;
    if (temp_v0 == 0) {
        func_80146C3C();
        return;
    }
    func_800D22E4(arg0);
    temp_v0_2 = arg0->unk10;
    temp_v1 = arg0->unk14;
    arg0->unk10 = (s32) (temp_v0_2 - (temp_v0_2 >> 4));
    temp_v0_3 = arg0->unk18;
    arg0->unk14 = (s32) (temp_v1 - (temp_v1 >> 4));
    arg0->unk18 = (s32) (temp_v0_3 - (temp_v0_3 >> 4));
}
