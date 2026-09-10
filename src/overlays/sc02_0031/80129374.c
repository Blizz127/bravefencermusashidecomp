/* SC02.CD FILE_031 / ov_SC02_031 retail span [80129374,80129398).
 * Offset 0x121C at overlay base 80128158. SHA256(span)=d3104ed8f18e83f68b7c95b1e5296cb4b3384ba8c53e9dd2b1e72c962513cea3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80129374.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8CA20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820010)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20014)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820014)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820018)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80129374 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Three-word copy (lw/sw x3). Body is m2c's verbatim with types
 * filled in. */

struct data_80129374 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_80129374(struct data_80129374 *arg0, struct data_80129374 *arg1) {
    arg0->unk10 = (s32) arg1->unk10;
    arg0->unk14 = (s32) arg1->unk14;
    arg0->unk18 = (s32) arg1->unk18;
}
#endif
