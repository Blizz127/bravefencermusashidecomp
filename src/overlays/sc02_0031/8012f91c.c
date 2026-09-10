/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012F91C,8012F968).
 * Offset 0x77C4 at overlay base 80128158. SHA256(span)=059acd0c77fe561288529916c2fb956232677580fe821eaf2275dd8075010b0b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012f91c.c (recovery=c, -O2); the span is
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
MUSASHI_NATIVE_MIPS_WORD(0x30420080)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C4D0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050017)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_8012F91C (main_0012.s), decoded manually from
 * raw asm (NOT verified against retail; C89-gated only,
 * promotion requires an oracle MATCH): F87C-sibling: when word
 * unkB4 & 0x80 calls 80131340(obj) (pass-through a0, nop delay
 * slot); ends with 31CA8(obj, 0x17). */

struct obj_8012F91C {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_80131340(void *arg0);
extern void func_80131CA8(void *arg0, s32 arg1);

void func_8012F91C(struct obj_8012F91C *arg0) {
    if (arg0->unkB4 & 0x80) {
        func_80131340(arg0);
    }
    func_80131CA8(arg0, 0x17);
}
#endif
