/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172608,8017261C).
 * Offset 0x4A4B0 at overlay base 80128158. SHA256(span)=cf1aabd2a0c5d4ebcb204fb3e7b4e177ac5132aea62731bab33c6bc8ff45f017.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172608.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8201F4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34420040)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201F4)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80172608 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word RMW setting bit 0x40 at +0x1F4 (lw/sw; same
 * flags word as the rest of the 801725xx cluster). Body is m2c's
 * verbatim with the member typed. */

struct data_80172608 {
    u8 pad[0x1F4];
    s32 unk1F4;
};

void func_80172608(struct data_80172608 *arg0) {
    arg0->unk1F4 = (s32) (arg0->unk1F4 | 0x40);
}
#endif
