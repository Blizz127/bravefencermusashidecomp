/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013A8B0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void *),
 * no frame, leaf. h0 = 0 (sh); w04 = 0 (sw rides the jr
 * delay slot, landing before return). Void: both callers
 * (my staged 39914/3995C, bare) ignore $v0, which is
 * untouched anyway. This confirms the inferred decl. */

struct st_8013A8B0 {
    u16 h0;
    u8 pad02[2];
    void *w04;
};

void func_8013A8B0(struct st_8013A8B0 *arg0) {
    arg0->h0 = 0;
    arg0->w04 = 0;
}
