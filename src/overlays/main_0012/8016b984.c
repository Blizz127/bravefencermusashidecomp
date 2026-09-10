/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8016B984 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk10/unk14/unk18 on a void*, each passed as an
 * s32 argument. The disassembly loads all three as words straight
 * into $a0 (lw +0x10/+0x14/+0x18), so the model declares three s32
 * members. Callee declarations follow the repo pipeline convention.
 * Body is m2c's verbatim. */

struct data_8016B984 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_80146C3C(void *);
void func_80016714();

void func_8016B984(struct data_8016B984 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = arg0->unk10;
    if (temp_a0 != 0) {
        func_80016714(temp_a0, 0x38);
    }
    temp_a0_2 = arg0->unk14;
    if (temp_a0_2 != 0) {
        func_80016714(temp_a0_2, 0x38);
    }
    temp_a0_3 = arg0->unk18;
    if (temp_a0_3 != 0) {
        func_80016714(temp_a0_3, 0x38);
    }
    func_80146C3C(arg0);
}
