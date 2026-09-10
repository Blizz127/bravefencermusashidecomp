/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139A44,80139A68).
 * Offset 0x118EC at overlay base 80128158. SHA256(span)=9e8eb721cd618f728d7b5e1e45aef9d5a2ead7d1e36a76dbde06d2d4f8104816.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139a44.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00051080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xAC247530)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
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
#endif
