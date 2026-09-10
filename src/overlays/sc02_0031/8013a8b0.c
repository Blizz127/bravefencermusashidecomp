/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013A8B0,8013A8BC).
 * Offset 0x12758 at overlay base 80128158. SHA256(span)=3d2fa21dd1a6925c4b8f2734ab787849d082d292acbfad8a2d08148a4064fc34.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013a8b0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xA4800000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800004)
#else
#include "psx_types.h"

/* HAND MODEL of func_8013A8B0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void *),
 * no frame, leaf. h0 = 0 (sh); w04 = 0 (sw rides the jr
 * delay slot, landing before return). Void: both callers
 * (my staged 39914/3995C, bare) ignore $v0, which is
 * untouched anyway. This confirms the inferred decl. */

struct st_8013A8B0 {
    u16 h0;
    u8 pad02[2];
    void *w04;
};

void func_8013A8B0(struct st_8013A8B0 *arg0) {
    arg0->h0 = 0;
    arg0->w04 = 0;
}
#endif
