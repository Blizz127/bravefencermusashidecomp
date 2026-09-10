/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F87C,8012F8C8).
 * Offset 0x7724 at overlay base 80128158. SHA256(span)=e8d6a62c27860c5a97e9050f912d96391f2ea121eeffa1bef7fcb0ab1216144a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f87c.c (recovery=c, -O2); the span is
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
MUSASHI_NATIVE_MIPS_WORD(0x30420008)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C4D0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x2405000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F87C (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): when word unkB4 & 8 calls
 * 80131340(obj) (a0 still holds obj at the jal with a nop delay
 * slot: pass-through arg, m2c showed none); ends with
 * 31CA8(obj, 0xA). */

struct obj_8012F87C {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_80131340(void *arg0);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F87C(struct obj_8012F87C *arg0) {
    if (arg0->unkB4 & 8) {
        func_80131340(arg0);
    }
    func_80131CA8(arg0, 0xA);
}
#endif
