/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012BF7C,8012BFA8).
 * Offset 0x3E24 at overlay base 80128158. SHA256(span)=240fdfe81a01d2abe1cd0414bfbccf72090bbbc8c39dc7d592c97bc89106f45d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012bf7c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8483000E)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x84426CB0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00621023)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021023)
MUSASHI_NATIVE_MIPS_WORD(0x28420360)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x38420001)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012BF7C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Halves grounded as lh (s16); bgez skip-negation then slti 0x360 matches the abs/compare shape (inversion after slti). */

extern s16 D_80126CB0;

struct pt_8012BF7C {
    u8 pad[0xE];
    s16 unkE;
};

s32 func_8012BF7C(struct pt_8012BF7C *arg0) {
    s32 var_v0;

    var_v0 = arg0->unkE - D_80126CB0;
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    return var_v0 >= 0x360;
}
#endif
