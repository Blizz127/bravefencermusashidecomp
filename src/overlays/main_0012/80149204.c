/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80149204 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Two word zero-stores at +0x1DC/+0x1E4 (sw $zero).
 * Body is m2c's verbatim with the members typed. */

struct data_80149204 {
    u8 pad[0x1DC];
    s32 unk1DC;
    u8 pad2[4];
    s32 unk1E4;
};

void func_80149204(struct data_80149204 *arg0) {
    arg0->unk1E4 = 0;
    arg0->unk1DC = 0;
}
