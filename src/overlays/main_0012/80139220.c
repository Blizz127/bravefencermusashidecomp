/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80139220 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s32 (struct *),
 * 0x18 frame. rem = ((s32)lhu(h12) + 1) % ((s32)lh(h2E) + 1)
 * -- the div/break-7/break-6 guards and mfhi prove a signed
 * % source (the INT_MIN/-1 guard is dead in-domain: the
 * dividend never reaches 0x80000000). h14 = 0; h12 =
 * (u16)rem (sh rides the 39DC8 jal delay slot, landing
 * before its body); func_80139DC8() (0-arg); v1 = (s32)lhu(h12)
 * - lhu(h16) (fresh re-read: 39DC8 may clobber h12). If
 * (v1 == -1 || v1 >= (s32)lh(h2E)): func_801392C8(s0),
 * return 1 (v0 = 1 is a plain insn overwriting 392C8's
 * return). Else return 0 (v0 = 0 rides the delay slot).
 * The s32 return is observed by func_8013914C; the 380E0 /
 * 387B8 call sites ignore it. */

struct st_80139220 {
    u8 pad00[0x12];
    u16 h12;
    u16 h14;
    u16 h16;
    u8 pad18[0x16];
    s16 h2E;
};

extern void func_80139DC8(void);
extern void func_801392C8(void *arg0);

s32 func_80139220(struct st_80139220 *arg0) {
    s32 v1v;

    arg0->h14 = 0;
    arg0->h12 = (u16)(((s32)arg0->h12 + 1) % ((s32)arg0->h2E + 1));
    func_80139DC8();
    v1v = (s32)arg0->h12 - (s32)arg0->h16;
    if (v1v == -1 || v1v >= (s32)arg0->h2E) {
        func_801392C8(arg0);
        return 1;
    }
    return 0;
}
