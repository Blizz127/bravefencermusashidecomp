/* SC02.CD FILE_031 / ov_SC02_031 retail span [801392C8,801392FC).
 * Offset 0x11170 at overlay base 80128158. SHA256(span)=0815f425158a92060a765293339cc3693cef7a73853fd6a20477877184ae49a3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801392c8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04E575)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0xA200001E)
MUSASHI_NATIVE_MIPS_WORD(0xA6020004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801392C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x18 frame. func_801395D4(a0) (s0 = a0 rides the jal delay
 * slot, so a0 flows untouched); b1E = 0; h04 = 5; return.
 * Void: the sole caller (func_80139220+0x88) overwrites $v0
 * with 1 right after the jal. 395D4 decl inferred (ahead;
 * its return is ignored here, re-verify at staging). */

struct st_801392C8 {
    u8 pad00[4];
    s16 h04;
    u8 pad06[0x18];
    u8 b1E;
};

extern void func_801395D4(void *arg0);

void func_801392C8(struct st_801392C8 *arg0) {
    func_801395D4(arg0);
    arg0->b1E = 0;
    arg0->h04 = 5;
}
#endif
