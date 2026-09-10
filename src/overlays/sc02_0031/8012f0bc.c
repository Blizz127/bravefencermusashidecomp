/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F0BC,8012F14C).
 * Offset 0x6F64 at overlay base 80128158. SHA256(span)=f04ad4b7ead982297473d32c419c109c6fe5a8dcaf7b369655ad711ad5914955.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f0bc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00030)
MUSASHI_NATIVE_MIPS_WORD(0x00C08021)
MUSASHI_NATIVE_MIPS_WORD(0x27A60020)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0034)
MUSASHI_NATIVE_MIPS_WORD(0x8C820014)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00621823)
MUSASHI_NATIVE_MIPS_WORD(0xAFA30010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820018)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30004)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00621823)
MUSASHI_NATIVE_MIPS_WORD(0xAFA30014)
MUSASHI_NATIVE_MIPS_WORD(0x8C82001C)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30008)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00621823)
MUSASHI_NATIVE_MIPS_WORD(0x0C013541)
MUSASHI_NATIVE_MIPS_WORD(0xAFA30018)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAE020000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20024)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAE020004)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20028)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAE020008)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0034)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00030)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F0BC (main_0012.s), decoded manually from
 * raw asm (0x90 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): sibling of
 * func_8012F038 with word inputs: builds an s32 triple of
 * arg1[0/4/8] - (arg0[0x14/0x18/0x1C] << 16) (lw/sll/subu),
 * runs func_8004D504(arg0, in, out) (a0 passes through: the jal
 * sets only a1/a2, verified against raw; m2c dropped it), and stores the three result words
 * to out[0/4/8] (sw). */

struct in_8012F0BC {
    u8 pad[0x14];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct win_8012F0BC {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct wout_8012F0BC {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F0BC(struct in_8012F0BC *arg0, struct win_8012F0BC *arg1, struct wout_8012F0BC *arg2) {
    s32 in[3];
    s32 out[3];

    in[0] = arg1->unk0 - (arg0->unk14 << 16);
    in[1] = arg1->unk4 - (arg0->unk18 << 16);
    in[2] = arg1->unk8 - (arg0->unk1C << 16);
    func_8004D504(arg0, in, out);
    arg2->unk0 = out[0];
    arg2->unk4 = out[1];
    arg2->unk8 = out[2];
}
#endif
