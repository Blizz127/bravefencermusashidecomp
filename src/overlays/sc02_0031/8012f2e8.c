/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F2E8,8012F374).
 * Offset 0x7190 at overlay base 80128158. SHA256(span)=be7a5a7deece95e240bd19d3a3f88e506c6017e9eb29c688fcef694621a0051a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f2e8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0034)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00030)
MUSASHI_NATIVE_MIPS_WORD(0x8C840020)
MUSASHI_NATIVE_MIPS_WORD(0x84A20000)
MUSASHI_NATIVE_MIPS_WORD(0x8C830048)
MUSASHI_NATIVE_MIPS_WORD(0x00C08021)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x84A20002)
MUSASHI_NATIVE_MIPS_WORD(0x8C83004C)
MUSASHI_NATIVE_MIPS_WORD(0x27A60020)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20014)
MUSASHI_NATIVE_MIPS_WORD(0x8C830050)
MUSASHI_NATIVE_MIPS_WORD(0x24840034)
MUSASHI_NATIVE_MIPS_WORD(0x84A20004)
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

/* HAND MODEL of func_8012F2E8 (main_0012.s), decoded manually from
 * raw asm (0x8C bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): F038-variant keyed
 * off the target words: builds an s32 triple of (s16)arg1[0/2/4]
 * minus target words +0x48/+0x4C/+0x50 (lh/lw/subu), runs
 * func_8004D504(unk20 + 0x34, in, out) (a0 = unk20 + 0x34 in the
 * jal delay slot; 8004D504 writes results through a2), and
 * stores the three result words as halfwords to out[0/2/4]. */

struct obj_8012F2E8 {
    u8 pad[0x20];
    void *unk20;
};

struct tgt_8012F2E8 {
    u8 pad[0x48];
    s32 unk48;
    s32 unk4C;
    s32 unk50;
};

struct u16in_8012F2E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

struct out_8012F2E8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F2E8(struct obj_8012F2E8 *arg0, struct u16in_8012F2E8 *arg1, struct out_8012F2E8 *arg2) {
    struct tgt_8012F2E8 *t;
    s32 in[3];
    s32 out[3];

    t = (struct tgt_8012F2E8 *) arg0->unk20;
    in[0] = arg1->unk0 - t->unk48;
    in[1] = arg1->unk2 - t->unk4C;
    in[2] = arg1->unk4 - t->unk50;
    func_8004D504((u8 *) t + 0x34, in, out);
    arg2->unk0 = (s16) out[0];
    arg2->unk2 = (s16) out[1];
    arg2->unk4 = (s16) out[2];
}
#endif
