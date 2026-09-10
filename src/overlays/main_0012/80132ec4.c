/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80132EC4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): frameless 2-arg void.
 * If arg0[0] == 0, returns at once; else do { arg0+4 = (u16)arg1;
 * arg0 += 8; } while (arg0[0] != 0). The sh truncates arg1 to its
 * low halfword; stride-8 nodes modelled as {s32, u16, pad}. */

struct node_80132EC4 {
    s32 unk0;
    u16 unk4;
    u8 pad[0x2];
};

void func_80132EC4(struct node_80132EC4 *arg0, s32 arg1) {
    if (arg0->unk0 == 0) {
        return;
    }
    do {
        arg0->unk4 = arg1;
        arg0++;
    } while (arg0->unk0 != 0);
}
