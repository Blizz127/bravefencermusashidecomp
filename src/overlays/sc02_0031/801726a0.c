/* SC02.CD FILE_031 / ov_SC02_031 retail span [801726A0,801726AC).
 * Offset 0x4A548 at overlay base 80128158. SHA256(span)=912aced3db7096fd80fe1a6654663cc047b7e8f028544893938c913b2eed2923.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801726a0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C8201F4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30420040)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_801726A0 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Word bit-test at +0x1F4 (lw; same flags word as the
 * rest of the 801725xx cluster). Body is m2c's verbatim with the
 * member typed. */

struct data_801726A0 {
    u8 pad[0x1F4];
    s32 unk1F4;
};

s32 func_801726A0(struct data_801726A0 *arg0) {
    return arg0->unk1F4 & 0x40;
}
#endif
