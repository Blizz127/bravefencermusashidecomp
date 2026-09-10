/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801490E0 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halfword store of the s16 argument at +0x108 (sh).
 * Body is m2c's verbatim with the member typed. */

struct data_801490E0 {
    u8 pad[0x108];
    s16 unk108;
};

void func_801490E0(struct data_801490E0 *arg0, s16 arg1) {
    arg0->unk108 = arg1;
}
