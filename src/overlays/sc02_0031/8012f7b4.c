/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F7B4,8012F828).
 * Offset 0x765C at overlay base 80128158. SHA256(span)=9f91acef129877d32d6a36a57a0e5f88c5a16001d9af3cccf96f2e904637c1ac.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f7b4.c (recovery=c, -O2); the span is
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
MUSASHI_NATIVE_MIPS_WORD(0x30420004)
MUSASHI_NATIVE_MIPS_WORD(0x1040000D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AFBA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8E03001C)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x14620008)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C68D)
MUSASHI_NATIVE_MIPS_WORD(0x24050008)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C68D)
MUSASHI_NATIVE_MIPS_WORD(0x24050020)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050007)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F7B4 (main_0012.s), decoded manually from
 * raw asm (0x74 bytes; m2c BEE8() misread corrected: the jal has
 * a nop delay slot with a0 still holding obj, so it is
 * BEE8(arg0) by pass-through; NOT verified against retail;
 * C89-gated only, promotion requires an oracle MATCH): when word
 * unkB4 & 4, calls BEE8(obj); when word unk1C is 1 and
 * 31A34(obj, 8) returns 0, calls 31A34(obj, 0x20). Always ends
 * with 31CA8(obj, 7). */

struct obj_8012F7B4 {
    u8 pad[0x1C];
    s32 unk1C;
    u8 pad2[0xB4 - 0x20];
    s32 unkB4;
};

extern s32 func_8012BEE8(void *arg0);
extern s32 func_80131A34(void *arg0, s32 arg1);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F7B4(struct obj_8012F7B4 *arg0) {
    if (arg0->unkB4 & 4) {
        func_8012BEE8(arg0);
        if (arg0->unk1C == 1 && func_80131A34(arg0, 8) == 0) {
            func_80131A34(arg0, 0x20);
        }
    }
    func_80131CA8(arg0, 7);
}
#endif
