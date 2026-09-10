/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012B21C,8012B23C).
 * Offset 0x30C4 at overlay base 80128158. SHA256(span)=2d141243bfdca1485d4387e60305141f5dcc6e8b50a7465580e985bc6b3c9bca.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012b21c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3402C000)
MUSASHI_NATIVE_MIPS_WORD(0xAC800018)
MUSASHI_NATIVE_MIPS_WORD(0xAC800014)
MUSASHI_NATIVE_MIPS_WORD(0xAC800010)
MUSASHI_NATIVE_MIPS_WORD(0xAC80004C)
MUSASHI_NATIVE_MIPS_WORD(0xAC800044)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820048)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012B21C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All stores grounded as sw; unk48 tiny-const via ori 0xC000. */

struct obj_8012B200 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x28];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

void func_8012B21C(struct obj_8012B200 *arg0) {
    arg0->unk18 = 0;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk4C = 0;
    arg0->unk44 = 0;
    arg0->unk48 = 0xC000;
}
#endif
