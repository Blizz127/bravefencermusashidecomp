/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80139634 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x20 frame. tmp (sp+0x10) = [lhu(h38), lhu(h3A), 0x38,
 * 0x30] (the tmp[1] store rides the jal delay slot, landing
 * before the call); func_80059888(tmp, 0, 0, 0); return.
 * Leaner twin of func_801395D4 (raw h3A, 0x30 instead of
 * h3A + h12*12 / 0xC). Void: both callers (func_80137840,
 * func_801391F0) ignore $v0, matching their staged void
 * decls. 59888 decl: void 4-arg here; main.s sites noted
 * for 59888's own staging. */

struct st_80139634 {
    u8 pad00[0x38];
    u16 h38;
    u16 h3A;
};

extern void func_80059888(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80139634(struct st_80139634 *arg0) {
    u16 tmp[4];

    tmp[0] = arg0->h38;
    tmp[1] = arg0->h3A;
    tmp[2] = 0x38;
    tmp[3] = 0x30;
    func_80059888(tmp, 0, 0, 0);
}
