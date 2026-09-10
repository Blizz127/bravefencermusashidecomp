/* SC02.CD FILE_031 / ov_SC02_031 retail span [801320D8,80132144).
 * Offset 0x9F80 at overlay base 80128158. SHA256(span)=86297d9fbdfe92ca6af3af1c6b79fe00c3a5c12f265904011ff26f020326a2e2.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017E8B0 here is D_8017F138 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B06E)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0xAE020020)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B2B9)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0804C84C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x0C007085)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x3C028018)
MUSASHI_NATIVE_MIPS_WORD(0x2442F138)
MUSASHI_NATIVE_MIPS_WORD(0xAE020058)
MUSASHI_NATIVE_MIPS_WORD(0x96020002)
MUSASHI_NATIVE_MIPS_WORD(0x24030080)
MUSASHI_NATIVE_MIPS_WORD(0xA603005C)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA6020002)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801320D8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): res = func_8012C1B8(arg0)
 * always stored to arg0+0x20 (delay slot, even NULL); NULL takes the
 * func_8012CAE4(arg0) path, else func_8001C214(res, 0), arg0+0x58 =
 * D_8017F138, arg0+0x5C = 0x80, arg0+0x2 += 1. Clone-twin of
 * func_80132144/801321B0/8013221C, verified from raw asm to differ
 * only in the table symbol. Same 8012C1B8 1-arg/pointer-out note as
 * func_80132018. */

struct obj_801320D8 {
    u8 pad0[0x2];
    u16 unk2;
    u8 pad1[0x1C];
    s32 unk20;
    u8 pad2[0x34];
    void *unk58;
    u16 unk5C;
};

extern s32 func_8012C1B8(void *arg0);
extern void func_8012CAE4(void *arg0);
extern void func_8001C214(s32 arg0, s32 arg1);
extern u8 D_8017F138[];

void func_801320D8(struct obj_801320D8 *arg0) {
    s32 res;

    res = func_8012C1B8(arg0);
    arg0->unk20 = res;
    if (res == 0) {
        func_8012CAE4(arg0);
        return;
    }
    func_8001C214(res, 0);
    arg0->unk58 = D_8017F138;
    arg0->unk5C = 0x80;
    arg0->unk2 = arg0->unk2 + 1;
}
#endif
