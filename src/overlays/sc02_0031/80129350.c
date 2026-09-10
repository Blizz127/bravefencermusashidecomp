/* SC02.CD FILE_031 / ov_SC02_031 retail span [80129350,80129374).
 * Offset 0x11F8 at overlay base 80128158. SHA256(span)=d3f24eea8713d674c4678beefacccb6b17867bc1597b6c898051313c06ef740e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80129350.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820008)
MUSASHI_NATIVE_MIPS_WORD(0x8CA2000C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC82000C)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80129350 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Three-word copy (lw/sw x3). Body is m2c's verbatim with types
 * filled in. */

struct data_80129350 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
};

void func_80129350(struct data_80129350 *arg0, struct data_80129350 *arg1) {
    arg0->unk4 = (s32) arg1->unk4;
    arg0->unk8 = (s32) arg1->unk8;
    arg0->unkC = (s32) arg1->unkC;
}
#endif
