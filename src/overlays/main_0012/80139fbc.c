/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80139FBC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * no frame, leaf. If ((w08 & 0x800) == 0) return; else
 * w08 &= ~0x800 (-0x801 mask); h04 = 2; return. (Mirrors
 * func_80138C30's else arm as a standalone.) Void: no
 * direct jal/j callers in the overlay (jalr- or
 * cross-overlay-reached); the v0 = 2 leftover is
 * incidental. */

struct st_80139FBC {
    u8 pad00[4];
    s16 h04;
    u8 pad06[2];
    u32 w08;
};

void func_80139FBC(struct st_80139FBC *arg0) {
    if ((arg0->w08 & 0x800) == 0) {
        return;
    }
    arg0->w08 &= ~0x800;
    arg0->h04 = 2;
}
