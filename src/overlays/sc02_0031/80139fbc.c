/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139FBC,80139FE8).
 * Offset 0x11E64 at overlay base 80128158. SHA256(span)=7590f66ead938872c85af603969e14fd3bb6ef8c74bdb40059b6512afd6c454b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139fbc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30620800)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x2402F7FF)
MUSASHI_NATIVE_MIPS_WORD(0x00621024)
MUSASHI_NATIVE_MIPS_WORD(0xAC820008)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0xA4820004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80139FBC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * no frame, leaf. If ((w08 & 0x800) == 0) return; else
 * w08 &= ~0x800 (-0x801 mask); h04 = 2; return. (Mirrors
 * func_80138C30's else arm as a standalone.) Void: no
 * direct jal/j callers in the overlay (jalr- or
 * cross-overlay-reached); the v0 = 2 leftover is
 * incidental. */

struct st_80139FBC {
    u8 pad00[4];
    s16 h04;
    u8 pad06[2];
    u32 w08;
};

void func_80139FBC(struct st_80139FBC *arg0) {
    if ((arg0->w08 & 0x800) == 0) {
        return;
    }
    arg0->w08 &= ~0x800;
    arg0->h04 = 2;
}
#endif
