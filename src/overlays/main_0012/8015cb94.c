/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8015CB94 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shape: arg0->unk170 = 0 on a void*. The disassembly stores a
 * word of zero (sw $zero +0x170), so the model declares one s32 at
 * +0x170. func_80154A74 was missing from the draft's declarations
 * and is added per the repo pipeline convention. Body is m2c's
 * verbatim. */

struct data_8015CB94 {
    u8 pad[0x170];
    s32 unk170;
};

void func_801553C0();
void func_80154A74();

void func_8015CB94(struct data_8015CB94 *arg0) {
    arg0->unk170 = 0;
    func_801553C0();
    func_80154A74(arg0, 0x11);
}
