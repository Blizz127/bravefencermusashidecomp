/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012E8C4 (main_0012.s), decoded manually from
 * raw asm (0x1C bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): flips bit 31 of the
 * word at unk20 + 4 (xor with 0x80000000, sw). */

struct obj_8012E8C4 {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012E8C4 {
    u8 pad[4];
    s32 unk4;
};

void func_8012E8C4(struct obj_8012E8C4 *arg0) {
    struct tgt_8012E8C4 *t;

    t = (struct tgt_8012E8C4 *) arg0->unk20;
    t->unk4 ^= 0x80000000;
}
