/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139A68,80139A8C).
 * Offset 0x11910 at overlay base 80128158. SHA256(span)=3f1268d759d9e5670cfa7dde30be512caa773985e4f10fd25dc54db614167dcc.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139a68.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00051040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xA4247540)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
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
#endif
