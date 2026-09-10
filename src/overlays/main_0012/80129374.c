/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80129374 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Three-word copy (lw/sw x3). Body is m2c's verbatim with types
 * filled in. */

struct data_80129374 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_80129374(struct data_80129374 *arg0, struct data_80129374 *arg1) {
    arg0->unk10 = (s32) arg1->unk10;
    arg0->unk14 = (s32) arg1->unk14;
    arg0->unk18 = (s32) arg1->unk18;
}

