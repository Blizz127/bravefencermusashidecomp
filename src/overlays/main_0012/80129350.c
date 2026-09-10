/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80129350 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Three-word copy (lw/sw x3). Body is m2c's verbatim with types
 * filled in. */

struct data_80129350 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
};

void func_80129350(struct data_80129350 *arg0, struct data_80129350 *arg1) {
    arg0->unk4 = (s32) arg1->unk4;
    arg0->unk8 = (s32) arg1->unk8;
    arg0->unkC = (s32) arg1->unkC;
}

