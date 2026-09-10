/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F828,8012F87C).
 * Offset 0x76D0 at overlay base 80128158. SHA256(span)=9490031104735b040165f924010f01abc8a1f56d7fb0c9b2751704b135bd2c33.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017E6F0 here is D_8017EF78 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E0200B4)
MUSASHI_NATIVE_MIPS_WORD(0x24030004)
MUSASHI_NATIVE_MIPS_WORD(0x30420008)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0xA20300C1)
MUSASHI_NATIVE_MIPS_WORD(0x3C058018)
MUSASHI_NATIVE_MIPS_WORD(0x24A5EF78)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C45C)
MUSASHI_NATIVE_MIPS_WORD(0x2406000B)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050009)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F828 (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): unconditionally sets byte
 * unkC1 = 4 (sb in the beqz delay slot); when word unkB4 & 8
 * calls 80131170(obj, &D_8017EF78, 0xB) (a0 still holds obj at
 * the jal: pass-through first arg, m2c showed two); ends with
 * 31CA8(obj, 9). */

struct obj_8012F828 {
    u8 pad[0xB4];
    s32 unkB4;
    u8 pad2[0xC1 - 0xB8];
    u8 unkC1;
};

extern u8 D_8017EF78;
extern void func_80131170(void *arg0, void *arg1, s32 arg2);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F828(struct obj_8012F828 *arg0) {
    arg0->unkC1 = 4;
    if (arg0->unkB4 & 8) {
        func_80131170(arg0, &D_8017EF78, 0xB);
    }
    func_80131CA8(arg0, 9);
}
#endif
