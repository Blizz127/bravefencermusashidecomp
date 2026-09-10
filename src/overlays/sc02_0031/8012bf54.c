/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012BF54,8012BF68).
 * Offset 0x3DFC at overlay base 80128158. SHA256(span)=7be68cc08a1bb353b3eed372200e6b95ab5f4b11a8458b22aeca28963430316a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012bf54.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482005C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34428000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482005C)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BF54 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. lhu/sh pair grounded from raw asm (u16 bit set). */

struct obj_8012BF54 {
    u8 pad[0x5C];
    u16 unk5C;
};

void func_8012BF54(struct obj_8012BF54 *arg0) {
    arg0->unk5C |= 0x8000;
}
#endif
