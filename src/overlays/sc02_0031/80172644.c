/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172644,80172658).
 * Offset 0x4A4EC at overlay base 80128158. SHA256(span)=c9ffd279194050b6c0d2cd3ae96e31ab5f5ec7c1f06e89b79a807196fa4a097a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172644.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8201F4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34420200)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201F4)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80172644 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word RMW setting bit 0x200 at +0x1F4 (lw/sw; same
 * flags word as the rest of the 801725xx cluster). Body is m2c's
 * verbatim with the member typed. */

struct data_80172644 {
    u8 pad[0x1F4];
    s32 unk1F4;
};

void func_80172644(struct data_80172644 *arg0) {
    arg0->unk1F4 = (s32) (arg0->unk1F4 | 0x200);
}
#endif
