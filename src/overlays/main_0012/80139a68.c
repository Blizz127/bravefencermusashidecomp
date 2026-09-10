/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80139A68 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32, s32),
 * no frame. i = (u32)a1 & 0xFFFF (andi); if (i < 4u, sltiu)
 * D_80127540[i] = (u16)a0 (sh; the sll x2 rides the branch
 * delay slot); return. Halfword twin of func_80139A44 (whose
 * table holds pointers). No direct jal/j callers in the
 * overlay (jalr- or cross-overlay-reached). The u16 table
 * view agrees with func_80138AB4.c (D_80127540[h48] feeds
 * func_80139D04). */

extern u16 D_80127540[];

void func_80139A68(s32 arg0, s32 arg1) {
    u32 iv;

    iv = ((u32)arg1) & 0xFFFF;
    if (iv < 4) {
        D_80127540[iv] = (u16)arg0;
    }
}
