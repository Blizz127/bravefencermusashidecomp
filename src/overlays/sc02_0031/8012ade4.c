/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012ADE4,8012AE00).
 * Offset 0x2C8C at overlay base 80128158. SHA256(span)=df224b17f9960a88e4b46563f61a6a0d9288da4a2de3b9376d587239cf4d89a8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ade4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820038)
MUSASHI_NATIVE_MIPS_WORD(0x8C83003C)
MUSASHI_NATIVE_MIPS_WORD(0x8C850040)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0xAC830008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC85000C)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012ADE4 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All accesses grounded as lw/sw words from raw asm. */

struct obj_8012ADE4 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad2[0x28];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
};

void func_8012ADE4(struct obj_8012ADE4 *arg0) {
    arg0->unk4 = arg0->unk38;
    arg0->unk8 = arg0->unk3C;
    arg0->unkC = arg0->unk40;
}
#endif
