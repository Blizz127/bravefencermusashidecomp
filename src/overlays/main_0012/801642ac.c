/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801642AC (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk4C and arg0 + 4 on a void*. The disassembly
 * loads the member as a word (lw 0x4C($s1)) and passes arg0+4 as a
 * byte address (addiu $a1, $s1, 0x4), so the model declares one s32
 * at +0x4C and spells the +4 address with a (u8 *) cast — the same
 * addiu either way. Callee declarations follow the repo pipeline
 * convention (unchecked prototypes; s32 return where slti consumes
 * the result). Body is m2c's verbatim. */

struct data_801642AC {
    u8 pad[0x4C];
    s32 unk4C;
};

void func_80146CA0(void *);
void func_80146E90(void *, s32);
s32 func_80146E98(void *);
void func_80147324();
void func_80163764(void *);
void func_80164418();
s32 func_80013328();

void func_801642AC(struct data_801642AC *arg0) {
    s32 temp_s0;

    temp_s0 = arg0->unk4C;
    func_80164418();
    if ((func_80013328(temp_s0 + 4, (void *) ((u8 *) arg0 + 4)) < 0x28) || (func_80146E98(arg0) != 0)) {
        func_80146E90(arg0, 8);
        func_80147324(0x44A);
        func_80146CA0(arg0);
    }
    func_80163764(arg0);
}
