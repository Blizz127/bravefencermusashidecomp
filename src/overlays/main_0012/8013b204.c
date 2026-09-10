/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013B204 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void *,
 * struct *), 0x18 frame. a2 = a1 rides the prologue delay
 * slot; a3 = a0 likewise. If (lh(a2 + 0xC) != 0) return
 * (delay a3 dead). If (lh(a2 + 0) != 2) return (delay a2
 * += 8 dead). Else: 3B274(D_800A651C[lhu(D_800B9A02) * 5]
 * + (lhu(a3->h1A) << 2), lh(a3->h1C), (u8 *)a2 + 8) (the
 * v1 * 20 byte walk over word entries is index * 5; the
 * a0 sum rides the jal delay slot); return. D_800B9A02
 * decl mirrors func_801397B0.c (u16). 3B274 is a BLOCKED
 * GTE core -- decl (s32, s32, void *) provisional here,
 * ret ignored, re-verify if it ever stages. Void: the
 * sole caller lives inside BLOCKED func_8013AA24. */

struct st_8013B204 {
    s16 h00;
    u8 pad02[10];
    s16 h0C;
};

struct a3_8013B204 {
    u8 pad00[0x1A];
    u16 h1A;
    s16 h1C;
};

extern u16 D_800B9A02;
extern u32 D_800A651C[];
extern void func_8013B274(s32 arg0, s32 arg1, void *arg2);

void func_8013B204(struct a3_8013B204 *arg0, struct st_8013B204 *arg1) {
    if (arg1->h0C != 0) {
        return;
    }
    if (arg1->h00 != 2) {
        return;
    }
    func_8013B274((s32)(D_800A651C[(u32)D_800B9A02 * 5] + ((u32)arg0->h1A << 2)), arg0->h1C,
        (u8 *)arg1 + 8);
}
