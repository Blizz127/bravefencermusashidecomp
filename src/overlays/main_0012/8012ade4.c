/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012ADE4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All accesses grounded as lw/sw words from raw asm. */

struct obj_8012ADE4 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad2[0x28];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
};

void func_8012ADE4(struct obj_8012ADE4 *arg0) {
    arg0->unk4 = arg0->unk38;
    arg0->unk8 = arg0->unk3C;
    arg0->unkC = arg0->unk40;
}

