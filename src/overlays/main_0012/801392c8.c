/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801392C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. func_801395D4(a0) (s0 = a0 rides the jal delay
 * slot, so a0 flows untouched); b1E = 0; h04 = 5; return.
 * Void: the sole caller (func_80139220+0x88) overwrites $v0
 * with 1 right after the jal. 395D4 decl inferred (ahead;
 * its return is ignored here, re-verify at staging). */

struct st_801392C8 {
    u8 pad00[4];
    s16 h04;
    u8 pad06[0x18];
    u8 b1E;
};

extern void func_801395D4(void *arg0);

void func_801392C8(struct st_801392C8 *arg0) {
    func_801395D4(arg0);
    arg0->b1E = 0;
    arg0->h04 = 5;
}
