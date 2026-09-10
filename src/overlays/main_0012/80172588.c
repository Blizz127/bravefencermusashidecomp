/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80172588 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Single word zero-store at +0x1F4 (sw $zero). Body is
 * m2c's verbatim with the member typed. */

struct data_80172588 {
    u8 pad[0x1F4];
    s32 unk1F4;
};

void func_80172588(struct data_80172588 *arg0) {
    arg0->unk1F4 = 0;
}
