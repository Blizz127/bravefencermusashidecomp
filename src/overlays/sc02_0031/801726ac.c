/* SC02.CD FILE_031 / ov_SC02_031 retail span [801726AC,801726B8).
 * Offset 0x4A554 at overlay base 80128158. SHA256(span)=a83c91fee1e376764b0f0fb5a08b3c17641e5164349a63c970b1759aff40f4b4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801726ac.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8201F4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30420080)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801726AC (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word bit-test at +0x1F4 (lw; same flags word as the
 * rest of the 801725xx cluster). Body is m2c's verbatim with the
 * member typed. */

struct data_801726AC {
    u8 pad[0x1F4];
    s32 unk1F4;
};

s32 func_801726AC(struct data_801726AC *arg0) {
    return arg0->unk1F4 & 0x80;
}
#endif
