/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012B23C,8012B260).
 * Offset 0x30E4 at overlay base 80128158. SHA256(span)=5f0f873c2f6d20e722c043f617fdf1d2769f5efd372cbdcfe6cbf09134e8b933.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012b23c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C020001)
MUSASHI_NATIVE_MIPS_WORD(0x34428000)
MUSASHI_NATIVE_MIPS_WORD(0xAC800018)
MUSASHI_NATIVE_MIPS_WORD(0xAC800014)
MUSASHI_NATIVE_MIPS_WORD(0xAC800010)
MUSASHI_NATIVE_MIPS_WORD(0xAC80004C)
MUSASHI_NATIVE_MIPS_WORD(0xAC800044)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820048)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012B23C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All stores grounded as sw; unk48 = 0x18000 via lui/ori. */

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

void func_8012B23C(struct obj_8012B200 *arg0) {
    arg0->unk18 = 0;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk4C = 0;
    arg0->unk44 = 0;
    arg0->unk48 = 0x18000;
}
#endif
