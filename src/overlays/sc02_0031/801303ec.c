/* SC02.CD FILE_031 / ov_SC02_031 retail span [801303EC,80130438).
 * Offset 0x8294 at overlay base 80128158. SHA256(span)=a59766a8b25e55621734f6362ec7ef1b76f029843e4a21308bc10d7c87f289cf.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801303ec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E0200B4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420010)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C678)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x2405000C)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801303EC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): if s0->unkB4 & 0x10,
 * func_801319E0(s0, arg1) (a0 = s0 live, a1 passes through
 * untouched; nop delay slot). Then func_80131CA8(s0, 0xC)
 * (result ignored). Returns void. */

struct obj_801303EC {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_801319E0(void *arg0, s32 arg1);
extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_801303EC(struct obj_801303EC *arg0, s32 arg1) {
    if (arg0->unkB4 & 0x10) {
        func_801319E0(arg0, arg1);
    }
    func_80131CA8(arg0, 0xC);
}
#endif
