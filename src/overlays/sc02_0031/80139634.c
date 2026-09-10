/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139634,80139680).
 * Offset 0x114DC at overlay base 80128158. SHA256(span)=d434b54cc1a6b562128b1f565ba6b40cfe31910cab9ee3efbaefc4bbc98acec8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139634.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x94820038)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9483003A)
MUSASHI_NATIVE_MIPS_WORD(0x24020038)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x24020030)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20016)
MUSASHI_NATIVE_MIPS_WORD(0x0C016622)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80139634 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x20 frame. tmp (sp+0x10) = [lhu(h38), lhu(h3A), 0x38,
 * 0x30] (the tmp[1] store rides the jal delay slot, landing
 * before the call); func_80059888(tmp, 0, 0, 0); return.
 * Leaner twin of func_801395D4 (raw h3A, 0x30 instead of
 * h3A + h12*12 / 0xC). Void: both callers (func_80137840,
 * func_801391F0) ignore $v0, matching their staged void
 * decls. 59888 decl: void 4-arg here; main.s sites noted
 * for 59888's own staging. */

struct st_80139634 {
    u8 pad00[0x38];
    u16 h38;
    u16 h3A;
};

extern void func_80059888(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80139634(struct st_80139634 *arg0) {
    u16 tmp[4];

    tmp[0] = arg0->h38;
    tmp[1] = arg0->h3A;
    tmp[2] = 0x38;
    tmp[3] = 0x30;
    func_80059888(tmp, 0, 0, 0);
}
#endif
