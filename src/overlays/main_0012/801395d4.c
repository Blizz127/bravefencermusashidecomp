/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801395D4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x20 frame. tmp (sp+0x10) = [h38, h3A + h12*12, 0x38,
 * 0xC] (the tmp[1] store rides the jal delay slot, landing
 * before the call); func_80059888(tmp, 0, 0, 0); return.
 * Void: the sole caller (func_801392C8) ignores $v0, and so
 * does the second 59888 site (80139668); main.s sites noted
 * for 59888's own staging. 59888 decl: void 4-arg here,
 * re-verify at staging. */

struct st_801395D4 {
    u8 pad00[0x12];
    u16 h12;
    u8 pad14[0x24];
    u16 h38;
    u16 h3A;
};

extern void func_80059888(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801395D4(struct st_801395D4 *arg0) {
    u16 tmp[4];

    tmp[0] = arg0->h38;
    tmp[1] = (u16)(arg0->h3A + (arg0->h12 * 12));
    tmp[2] = 0x38;
    tmp[3] = 0xC;
    func_80059888(tmp, 0, 0, 0);
}
