/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80139A44 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void *,
 * s32), no frame. i = (u32)a1 & 0xFFFF (andi); if (i < 4u,
 * sltiu) D_80127530[i] = a0 (sw; the sll x4 rides the branch
 * delay slot, so the indexed store is the array write);
 * return. No direct jal/j callers in the overlay (jalr- or
 * cross-overlay-reached, as with func_80139A34). The u8*
 * table view agrees with func_801380E0.c / func_801387B8.c
 * (D_80127530[h4A] byte-string bases); the void* param
 * assigns implicitly. */

extern u8 *D_80127530[];

void func_80139A44(void *arg0, s32 arg1) {
    u32 iv;

    iv = ((u32)arg1) & 0xFFFF;
    if (iv < 4) {
        D_80127530[iv] = arg0;
    }
}
