/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128D60,80128DB4).
 * Offset 0xC08 at overlay base 80128158. SHA256(span)=33ff2bb617b6b146695f0fd19c26036bcbb1a9acdd0542e9225f60f5aa71c0b9.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80128d60.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xACA60000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A00004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042003F)
MUSASHI_NATIVE_MIPS_WORD(0x10800006)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20006)
MUSASHI_NATIVE_MIPS_WORD(0x8CC50000)
MUSASHI_NATIVE_MIPS_WORD(0x0C006114)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804A369)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC40000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0060F8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80128D60 (main_0012.s), decoded manually from
 * raw asm (fully visible; m2c 80018450-arity corrected: the
 * `lw a1, 0(a2)` before the jal is deliberate, and a0 still
 * holds incoming arg0, so the call is 2-arg; NOT verified
 * against retail; C89-gated only, promotion requires an oracle
 * MATCH): stores arg1->unk0 = arg2 (sw) and u16 arg1->unk4 = 0
 * (sh); stores (u16)(*(s32 *)(arg2 + 4) & 0x3F) at arg1 + 6
 * (beqz delay slot: always). Nonzero arg0 calls
 * 80018450(arg0, arg2->unk0); zero arg0 calls
 * 800183E0(arg2->unk0). arg0 is a pointer (80018450 dereferences
 * a0 at +0x28/+0x2A/+0x27; verified in its body), NULL-checked
 * by the beqz; 800183E0 zeroes a1/a2 on entry (1-arg) and
 * 80018450 zeroes a2/a3 (2-arg), so extra regs at these sites
 * are dead. */

struct obj_80128D60 {
    void *unk0;
    u16 unk4;
    u16 unk6;
};

struct src_80128D60 {
    s32 unk0;
    s32 unk4;
};

extern void func_80018450(void *arg0, s32 arg1);
extern void func_800183E0(s32 arg0);

void func_80128D60(void *arg0, struct obj_80128D60 *arg1, struct src_80128D60 *arg2) {
    arg1->unk0 = arg2;
    arg1->unk4 = 0;
    arg1->unk6 = (u16) (arg2->unk4 & 0x3F);
    if (arg0 != 0) {
        func_80018450(arg0, arg2->unk0);
    } else {
        func_800183E0(arg2->unk0);
    }
}
#endif
