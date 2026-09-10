/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128EA8,80128ED8).
 * Offset 0xD50 at overlay base 80128158. SHA256(span)=430f480c56f9e800de1a7b97a5f6c5e421f84016a902f1276b0a9f15afca844f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80128ea8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0xACA60000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A00004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042003F)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20006)
MUSASHI_NATIVE_MIPS_WORD(0x94C20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820028)
MUSASHI_NATIVE_MIPS_WORD(0x94C20002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482002A)
#else
#include "psx_types.h"

/* HAND MODEL of func_80128EA8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): stores arg1->unk0
 * = arg2 (sw), u16 arg1->unk4 = 0 (sh), u16 arg1->unk6 =
 * *(s32 *)(arg2 + 4) & 0x3F (lw/andi/sh), u16 arg0->unk28 =
 * lhu(arg2 + 0), u16 arg0->unk2A = lhu(arg2 + 2) (the last in
 * the jr delay slot). */

struct obj_80128EA8 {
    void *unk0;
    u16 unk4;
    u16 unk6;
};

struct src_80128EA8 {
    u16 unk0;
    u16 unk2;
    s32 unk4;
};

struct dst_80128EA8 {
    u8 pad[0x28];
    u16 unk28;
    u16 unk2A;
};

void func_80128EA8(struct dst_80128EA8 *arg0, struct obj_80128EA8 *arg1, struct src_80128EA8 *arg2) {
    arg1->unk0 = arg2;
    arg1->unk4 = 0;
    arg1->unk6 = (u16) (arg2->unk4 & 0x3F);
    arg0->unk28 = arg2->unk0;
    arg0->unk2A = arg2->unk2;
}
#endif
