/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012D624,8012D664).
 * Offset 0x54CC at overlay base 80128158. SHA256(span)=2543969916115e89a6c11e6fe83adf949004f7b03b2f8b75390f1a129c03d603.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012d624.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x94820006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x9482000E)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B599)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012D624 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Triple init grounded as lhu (u16); the third half is stored in the jal delay slot. a1/a2 pass through untouched to func_8012D664 (true 3-parameter signature; m2c missed the forwarding), and the call result is returned (v0 untouched to jr). */

extern s32 func_8012D664(void *arg0, s32 arg1, void *arg2);

s32 func_8012D624(void *arg0, s32 arg1, void *arg2) {
    u16 h[3];

    h[0] = ((u16 *) arg0)[3];
    h[1] = ((u16 *) arg0)[5];
    h[2] = ((u16 *) arg0)[7];
    return func_8012D664(h, arg1, arg2);
}
#endif
