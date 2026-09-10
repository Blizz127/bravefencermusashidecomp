/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013A4C4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. a1 = lw(a0 + 4) (sub-object); h0E = 0 (sh).
 * a1->h28 -= 0x400; v0 = lhu(a1->h2A) - 0x400 (kept across
 * the test); sh(a1->h2A) = v0 rides the slti-branch delay
 * slot, landing on both edges (the fallthrough re-store
 * of the same value is unobservable, dropped). If
 * ((s16)lh(a1->h28-re-read) < 0x401, signed): a1->h2A = 0;
 * a1->h28 = 0; a0->h00 = 4; a0->h02 = 0;
 * w04 = NULL (sw rides the shared-epilogue jump delay
 * slot). Else (3A518): 3A530(a0) (a0 flows untouched).
 * h28/h2A are u16 (lhu) with one s16 re-read (same
 * mixed-view note as func_8013A448). Void: the sole
 * caller (func_8013A380) jumps away ignoring $v0. 3A530
 * decl void here (ret ignored; re-verify at staging). */

struct h_8013A4C4 {
    u8 pad00[0x28];
    u16 h28;
    u16 h2A;
};

struct st_8013A4C4 {
    u16 h00;
    u16 h02;
    struct h_8013A4C4 *w04;
    u8 pad08[6];
    u16 h0E;
};

extern void func_8013A530(void *arg0);

void func_8013A4C4(struct st_8013A4C4 *arg0) {
    struct h_8013A4C4 *a1v = arg0->w04;
    u16 sub;

    arg0->h0E = 0;
    a1v->h28 = (u16)(a1v->h28 - 0x400);
    sub = (u16)(a1v->h2A - 0x400);
    a1v->h2A = sub;
    if ((s16)a1v->h28 < 0x401) {
        a1v->h2A = 0;
        a1v->h28 = 0;
        arg0->h00 = 4;
        arg0->h02 = 0;
        arg0->w04 = 0;
    } else {
        func_8013A530(arg0);
    }
}
