/* SC02.CD FILE_031 / ov_SC02_031 retail span [801395D4,80139634).
 * Offset 0x1147C at overlay base 80128158. SHA256(span)=0c7ddc1e44be2fe417175ece8e98d9734a06e743e6b765f9d62d4fcb5626d967.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801395d4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x94820038)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x94850012)
MUSASHI_NATIVE_MIPS_WORD(0x9483003A)
MUSASHI_NATIVE_MIPS_WORD(0x24020038)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x2402000C)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20016)
MUSASHI_NATIVE_MIPS_WORD(0x00051040)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C016622)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801395D4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (struct *),
 * 0x20 frame. tmp (sp+0x10) = [h38, h3A + h12*12, 0x38,
 * 0xC] (the tmp[1] store rides the jal delay slot, landing
 * before the call); func_80059888(tmp, 0, 0, 0); return.
 * Void: the sole caller (func_801392C8) ignores $v0, and so
 * does the second 59888 site (80139668); main.s sites noted
 * for 59888's own staging. 59888 decl: void 4-arg here,
 * re-verify at staging. */

struct st_801395D4 {
    u8 pad00[0x12];
    u16 h12;
    u8 pad14[0x24];
    u16 h38;
    u16 h3A;
};

extern void func_80059888(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801395D4(struct st_801395D4 *arg0) {
    u16 tmp[4];

    tmp[0] = arg0->h38;
    tmp[1] = (u16)(arg0->h3A + (arg0->h12 * 12));
    tmp[2] = 0x38;
    tmp[3] = 0xC;
    func_80059888(tmp, 0, 0, 0);
}
#endif
