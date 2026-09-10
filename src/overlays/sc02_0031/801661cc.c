/* SC02.CD FILE_031 / ov_SC02_031 retail span [801661CC,80166244).
 * Offset 0x3E074 at overlay base 80128158. SHA256(span)=166054c947dcf79babd614ef0fde332722ef229ee2516abcc77ed01ff140004f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801661cc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E040020)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A3B6)
MUSASHI_NATIVE_MIPS_WORD(0x26050024)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B0F)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0805988C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0348B9)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8E020010)
MUSASHI_NATIVE_MIPS_WORD(0x8E040018)
MUSASHI_NATIVE_MIPS_WORD(0x00021843)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x00041043)
MUSASHI_NATIVE_MIPS_WORD(0x00042083)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAE030010)
MUSASHI_NATIVE_MIPS_WORD(0xAE020018)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801661CC (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk20/unk10/unk18 on a void*, plus arg0 + 0x24
 * passed as an address. The disassembly loads/stores the members as
 * words (lw +0x20/+0x10/+0x18, sw +0x10/+0x18) and computes the
 * address with a byte addiu ($a1, $s0, 0x24), so the model declares
 * three s32 members and spells the address with a (u8 *) cast — the
 * same addiu either way. Callee declarations follow the repo pipeline
 * convention. Body is m2c's verbatim. */

struct data_801661CC {
    u8 pad[0x10];
    s32 unk10;
    u8 pad2[0x4];
    s32 unk18;
    u8 pad3[0x4];
    s32 unk20;
};

s32 func_80128ED8(s32, void *);
void func_80146C3C(void *);
void func_800D22E4();

void func_801661CC(struct data_801661CC *arg0) {
    s32 temp_a0;
    s32 temp_v0;

    if (func_80128ED8(arg0->unk20, (void *) ((u8 *) arg0 + 0x24)) != 0) {
        func_80146C3C(arg0);
        return;
    }
    func_800D22E4(arg0);
    temp_v0 = arg0->unk10;
    temp_a0 = arg0->unk18;
    arg0->unk10 = (s32) ((temp_v0 >> 1) + (temp_v0 >> 2));
    arg0->unk18 = (s32) ((temp_a0 >> 1) + (temp_a0 >> 2));
}
#endif
