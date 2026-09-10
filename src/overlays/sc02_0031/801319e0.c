/* SC02.CD FILE_031 / ov_SC02_031 retail span [801319E0,80131A34).
 * Offset 0x9888 at overlay base 80128158. SHA256(span)=44508efda94b3f706749a92198aecfeaca8e023857b3c59a76bca14c2a7ce29f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801319e0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x14400009)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8E020078)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A813)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B086)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801319E0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): incoming a1 is dead
 * (overwritten by the first jal delay slot). If
 * func_80131CA8(s0, 0x11) == 0: when word s0->unk78 != 0,
 * func_8002A04C(s0); then func_8012C218(s0). Returns void. */

struct obj_801319E0 {
    u8 pad[0x78];
    u32 unk78;
};

extern s32 func_80131CA8(void *arg0, s32 arg1);
extern void func_8002A04C(void *arg0);
extern void func_8012C218(void *arg0);

void func_801319E0(struct obj_801319E0 *arg0) {
    if (func_80131CA8(arg0, 0x11) == 0) {
        if (arg0->unk78 != 0) {
            func_8002A04C(arg0);
        }
        func_8012C218(arg0);
    }
}
#endif
