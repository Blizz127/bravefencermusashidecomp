/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801391F0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. h12 = 0; h14 = 0; func_80139634(a0) (the h16 =
 * 0 store rides the jal delay slot, so all three zeroes land
 * before 39634's body); func_80139DC8() (0-arg); return. Both
 * callee returns are ignored at every visible call site
 * (here and in func_80137840), so both are decl'd void
 * pending their own staging. */

struct st_801391F0 {
    u8 pad00[0x12];
    u16 h12;
    u16 h14;
    u16 h16;
};

extern void func_80139634(void *arg0);
extern void func_80139DC8(void);

void func_801391F0(struct st_801391F0 *arg0) {
    arg0->h12 = 0;
    arg0->h14 = 0;
    arg0->h16 = 0;
    func_80139634(arg0);
    func_80139DC8();
}
