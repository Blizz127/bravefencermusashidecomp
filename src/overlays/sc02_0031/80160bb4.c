/* SC02.CD FILE_031 / ov_SC02_031 retail span [80160BB4,80160C28).
 * Offset 0x38A5C at overlay base 80128158. SHA256(span)=2fb1ec4fc8e65d3155653075682ddda3d42216a7a2bac5db480756e7db898b45.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80160bb4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E020044)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34420080)
MUSASHI_NATIVE_MIPS_WORD(0x0C0554EA)
MUSASHI_NATIVE_MIPS_WORD(0xAE020044)
MUSASHI_NATIVE_MIPS_WORD(0x0C055510)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C055054)
MUSASHI_NATIVE_MIPS_WORD(0x24050026)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x2405001E)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x24020FE9)
MUSASHI_NATIVE_MIPS_WORD(0xAC800234)
MUSASHI_NATIVE_MIPS_WORD(0xA4620010)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0xAC800238)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80160BB4 (main_0012.s): NOT verified
 * against retail. C89-gated only; promotion requires an oracle MATCH.
 * m2c shapes: arg0->unk44/unk234/unk238 and arg0->unk20->unk10.
 * The disassembly moves the outer three as words (lw/sw +0x44, sw
 * $zero +0x234/+0x238) and the inner one as a HALFWORD (sh +0x10
 * through the +0x20 pointer), so the inner member is u16 — a word
 * member would emit sw and mismatch. 0xFE9 fits the halfword.
 * func_80146CA0 was missing from the draft's declarations and is
 * added per the repo pipeline convention. Body is m2c's verbatim. */

struct inner_80160BB4 {
    u8 pad[0x10];
    u16 unk10;
};

struct data_80160BB4 {
    u8 pad[0x20];
    struct inner_80160BB4 *unk20;
    u8 pad2[0x20];
    s32 unk44;
    u8 pad3[0x1EC];
    s32 unk234;
    s32 unk238;
};

void func_80154150(void *, s32);
void func_80154A74(void *, s32);
void func_801553A8();
void func_80155440(void *);
void func_80146CA0();

void func_80160BB4(struct data_80160BB4 *arg0) {
    arg0->unk44 = (s32) (arg0->unk44 | 0x80);
    func_801553A8();
    func_80155440(arg0);
    func_80154150(arg0, 0x26);
    func_80154A74(arg0, 0x1E);
    arg0->unk234 = 0;
    arg0->unk20->unk10 = 0xFE9;
    arg0->unk238 = 0;
    func_80146CA0(arg0);
}
#endif
