/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013A9B4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *,
 * struct row *), 0x18 frame. Link op: v0 = a1 (row, kept
 * across the v1 = 1); row->h02 = 0 (sh); row->w04 = arg0
 * (sw); arg0->w40 = row (sw); row->h00 = 1 (sh, delay v1
 * dead); row->h0C = 0; row->h0E = 0 (sh pair);
 * 3A9F8(row, lhu(arg0->h18)) (a0 = row rides the jal delay
 * slot; the h0E zero lands first). The row writes prove
 * rows carry the full {h00,h02,w04,h0C,h0E} footprint --
 * the row struct here (and in func_8013A380.c /
 * func_8013A8FC.c) carries exactly that. Void: the sole
 * caller (my staged 3A8FC, bare) ignores $v0. 3A9F8 decl
 * mirrored (staged; its h0E store may overwrite the zero
 * just written, order preserved). */

struct row_8013A9B4 {
    s16 h00;
    u16 h02;
    void *w04;
    u8 pad08[4];
    u16 h0C;
    u16 h0E;
};

struct st_8013A9B4 {
    u8 pad00[0x18];
    u16 h18;
    u8 pad1A[0x26];
    void *w40;
};

extern void func_8013A9F8(void *arg0, s32 arg1);

void func_8013A9B4(struct st_8013A9B4 *arg0, struct row_8013A9B4 *arg1) {
    arg1->h02 = 0;
    arg1->w04 = arg0;
    arg0->w40 = arg1;
    arg1->h00 = 1;
    arg1->h0C = 0;
    arg1->h0E = 0;
    func_8013A9F8(arg1, arg0->h18);
}
