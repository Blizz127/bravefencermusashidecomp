/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172588,80172590).
 * Offset 0x4A430 at overlay base 80128158. SHA256(span)=84853b01ff32b3d672f9d0139c00c912b33a504dab988790e1ab2af7a7b935b1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172588.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC8001F4)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_80172588 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Single word zero-store at +0x1F4 (sw $zero). Body is
 * m2c's verbatim with the member typed. */

struct data_80172588 {
    u8 pad[0x1F4];
    s32 unk1F4;
};

void func_80172588(struct data_80172588 *arg0) {
    arg0->unk1F4 = 0;
}
#endif
