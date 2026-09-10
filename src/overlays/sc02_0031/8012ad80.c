/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012AD80,8012ADE4).
 * Offset 0x2C28 at overlay base 80128158. SHA256(span)=c2ac1419d02439af5611104dd8310dedcc7ac3da87f9782a26d191741c52c55d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ad80.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820010)
MUSASHI_NATIVE_MIPS_WORD(0x8C850044)
MUSASHI_NATIVE_MIPS_WORD(0x8C830014)
MUSASHI_NATIVE_MIPS_WORD(0x8C860048)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820018)
MUSASHI_NATIVE_MIPS_WORD(0x8C85004C)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0xAC830014)
MUSASHI_NATIVE_MIPS_WORD(0x8C830004)
MUSASHI_NATIVE_MIPS_WORD(0x8C860010)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820018)
MUSASHI_NATIVE_MIPS_WORD(0x8C820008)
MUSASHI_NATIVE_MIPS_WORD(0x8C850014)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0xAC830004)
MUSASHI_NATIVE_MIPS_WORD(0x8C83000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C860018)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x00661821)
MUSASHI_NATIVE_MIPS_WORD(0xAC820008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC83000C)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD80 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All accesses grounded as lw/sw/addu words from raw asm; order matches m2c exactly. */

struct obj_8012AD80 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x28];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

void func_8012AD80(struct obj_8012AD80 *arg0) {
    arg0->unk10 = arg0->unk10 + arg0->unk44;
    arg0->unk14 = arg0->unk14 + arg0->unk48;
    arg0->unk18 = arg0->unk18 + arg0->unk4C;
    arg0->unk4 = arg0->unk4 + arg0->unk10;
    arg0->unk8 = arg0->unk8 + arg0->unk14;
    arg0->unkC = arg0->unkC + arg0->unk18;
}
#endif
