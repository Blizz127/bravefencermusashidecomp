/* SC02.CD FILE_031 / ov_SC02_031 retail span [801292C8,8012931C).
 * Offset 0x1170 at overlay base 80128158. SHA256(span)=8244aa9f00ed4ff38a936a8a96b7340b155d38b5603c2f7bdafe1f4467b3ed57.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801292c8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E040020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10800008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x94830000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14620002)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x24050084)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801292C8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): loads word unk20;
 * when non-NULL calls func_80016714(unk20, tag == 1 ? 0x84 :
 * 0x38) (size chosen by the bne delay-slot pair); always zeroes
 * u16 unk0 (sh, shared exit). */

struct obj_801292C8 {
    u16 unk0;
    u8 pad[0x20 - 0x2];
    void *unk20;
};

extern void func_80016714(void *arg0, s32 arg1);

void func_801292C8(struct obj_801292C8 *arg0) {
    if (arg0->unk20 != 0) {
        func_80016714(arg0->unk20, *(u16 *) arg0->unk20 == 1 ? 0x84 : 0x38);
    }
    arg0->unk0 = 0;
}
#endif
