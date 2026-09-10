/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012931C,80129350).
 * Offset 0x11C4 at overlay base 80128158. SHA256(span)=8ba7a8502e27791f8b1444b8d8f5f268230990dbe4372e0a27587eb9b2b6ea56.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012931c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820004)
MUSASHI_NATIVE_MIPS_WORD(0x8C830010)
MUSASHI_NATIVE_MIPS_WORD(0x8C850014)
MUSASHI_NATIVE_MIPS_WORD(0x8C860018)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0x8C820008)
MUSASHI_NATIVE_MIPS_WORD(0x8C83000C)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0xAC820008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC83000C)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012931C (main_0012.s), decoded manually from
 * raw asm (fully visible, no frame; NOT verified against retail;
 * C89-gated only, promotion requires an oracle MATCH):
 * accumulates three word pairs: unk4 += unk10, unk8 += unk14,
 * unkC += unk18 (lw/addu/sw; the unkC store sits in the jr
 * delay slot). */

struct obj_8012931C {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_8012931C(struct obj_8012931C *arg0) {
    arg0->unk4 += arg0->unk10;
    arg0->unk8 += arg0->unk14;
    arg0->unkC += arg0->unk18;
}
#endif
