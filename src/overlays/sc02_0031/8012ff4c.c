/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012FF4C,8012FF98).
 * Offset 0x7DF4 at overlay base 80128158. SHA256(span)=4218ca9f458b030683a9b20ad2245dc3b8e8197c2529e5045e6e9cd779806192.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012ff4c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C8200B4)
MUSASHI_NATIVE_MIPS_WORD(0x24030005)
MUSASHI_NATIVE_MIPS_WORD(0x30420020)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0xA08300C1)
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x2402001E)
MUSASHI_NATIVE_MIPS_WORD(0xA480005C)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0xA4800098)
MUSASHI_NATIVE_MIPS_WORD(0xA4600010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x2405000F)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012FF4C (main_0012.s), decoded manually from
 * raw asm (0x4C bytes; m2c CA8(0xF) misread corrected: a0 is
 * never written, so obj passes through (this function keeps obj
 * in a0 throughout, no frame register); NOT verified against
 * retail; C89-gated only, promotion requires an oracle MATCH):
 * unconditionally sets byte unkC1 = 5 (sb in the beqz delay
 * slot); when word unkB4 & 0x20 zeroes u16 unk5C, stores word
 * unk1C = 0x1E (real sw), zeroes u16 unk98 and target halfword
 * +0x10. Ends with CA8(obj, 0xF). */

struct obj_8012FF4C {
    u8 pad[0x1C];
    s32 unk1C;
    void *unk20;
    u8 pad2[0x5C - 0x24];
    u16 unk5C;
    u8 pad3[0x98 - 0x5E];
    u16 unk98;
    u8 pad4[0xB4 - 0x9A];
    s32 unkB4;
    u8 pad5[0xC1 - 0xB8];
    u8 unkC1;
};

struct tgt_8012FF4C {
    u8 pad[0x10];
    u16 unk10;
};

extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012FF4C(struct obj_8012FF4C *arg0) {
    arg0->unkC1 = 5;
    if (arg0->unkB4 & 0x20) {
        arg0->unk5C = 0;
        arg0->unk1C = 0x1E;
        arg0->unk98 = 0;
        ((struct tgt_8012FF4C *) arg0->unk20)->unk10 = 0;
    }
    func_80131CA8(arg0, 0xF);
}
#endif
