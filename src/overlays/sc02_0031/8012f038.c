/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F038,8012F0BC).
 * Offset 0x6EE0 at overlay base 80128158. SHA256(span)=18422ec658f08f447f97422d8d1d23a43f7380f88e1cd7ffe10d4d65309447e1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f038.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0034)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00030)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0x8C830014)
MUSASHI_NATIVE_MIPS_WORD(0x00C08021)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x84A20002)
MUSASHI_NATIVE_MIPS_WORD(0x8C830018)
MUSASHI_NATIVE_MIPS_WORD(0x27A60020)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20014)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
MUSASHI_NATIVE_MIPS_WORD(0x8C83001C)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x0C013541)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020002)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20028)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6020004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0034)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00030)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F038 (main_0012.s), decoded manually from
 * raw asm (0x84 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): builds an s32 triple
 * of (s16)arg1[0/2/4] - (s32)arg0[0x14/0x18/0x1C] (lh/lw/subu),
 * runs func_8004D504(arg0, in, out) (a0 passes through: the jal
 * sets only a1/a2, verified against raw; m2c dropped it), and stores the three result words
 * as halfwords to out[0/2/4] (lw/sh). */

struct in_8012F038 {
    u8 pad[0x14];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct u16in_8012F038 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

struct out_8012F038 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F038(struct in_8012F038 *arg0, struct u16in_8012F038 *arg1, struct out_8012F038 *arg2) {
    s32 in[3];
    s32 out[3];

    in[0] = arg1->unk0 - arg0->unk14;
    in[1] = arg1->unk2 - arg0->unk18;
    in[2] = arg1->unk4 - arg0->unk1C;
    func_8004D504(arg0, in, out);
    arg2->unk0 = (s16) out[0];
    arg2->unk2 = (s16) out[1];
    arg2->unk4 = (s16) out[2];
}
#endif
