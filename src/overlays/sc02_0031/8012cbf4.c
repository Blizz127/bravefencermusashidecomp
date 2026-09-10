/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012CBF4,8012CC1C).
 * Offset 0x4A9C at overlay base 80128158. SHA256(span)=e0f23a418d387ab3d7d14650f6844ed48bf88acbec321d035f7e2590a13402d4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012cbf4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C06800D)
MUSASHI_NATIVE_MIPS_WORD(0x24C63918)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B322)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012CBF4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Passthrough wrapper: object in a0, mode 0x11 in the delay slot, &D_800D3918 in a2. */

struct obj_8012CC88 {
    u8 pad[4];
    s32 unk4;
    u16 unk6;
    s32 unk8;
    u16 unkA;
    s32 unkC;
    u16 unkE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x1E];
    u16 unk3A;
    u16 pad3;
    u16 unk3E;
    u16 pad4;
    u16 unk42;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

extern u16 D_800D3918[];

void func_8012CC88(struct obj_8012CC88 *arg0, s32 arg1, u16 *arg2);

void func_8012CBF4(struct obj_8012CC88 *arg0) {
    func_8012CC88(arg0, 0x11, D_800D3918);
}
#endif
