/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013A164 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * no frame, leaf. v1 = lw(w40); if (v1 == NULL) goto block.
 * If (lhu(h18) == 0) goto block (delay v0 = 2 dead). If
 * (lh(v1[0]) != 2, signed) return early (bne to the jr).
 * Block (3A194): w08 |= 0x1000 (sw rides the next beqz
 * delay slot, landing first); h04 = ((w08 & 0x10000) &&
 * lh(D_8012752C) && !(w08 & 0x40000)) ? 0x10 : 2 (the
 * 0x10/0x2 both ride jump delay slots; && short-circuits
 * in asm order). w40's slot is an s16 view here (lh +
 * compare); sibling files use a u16 tgt view for their
 * store-only w40[0] = 3 -- behaviorally identical slots,
 * load-insn choice noted for the oracle. D_8012752C is
 * s16 here (its only load); store-only files keep u16
 * (same object, noted). Void: no direct jal/j callers in
 * the overlay. */

struct st_8013A164 {
    u8 pad00[4];
    s16 h04;
    u8 pad06[2];
    u32 w08;
    u8 pad0C[0xC];
    u16 h18;
    u8 pad1A[0x26];
    s16 *w40;
};

extern s16 D_8012752C;

void func_8013A164(struct st_8013A164 *arg0) {
    s16 *w40v;
    u32 w08v;

    w40v = arg0->w40;
    if (w40v != 0 && arg0->h18 != 0 && *w40v != 2) {
        return;
    }
    w08v = arg0->w08 | 0x1000;
    arg0->w08 = w08v;
    if ((w08v & 0x10000) != 0 && D_8012752C != 0 && (w08v & 0x40000) == 0) {
        arg0->h04 = 0x10;
    } else {
        arg0->h04 = 2;
    }
}
