/* Overlay range [80171AB0,80171B10) from MAIN.CD member 0012.
 * SHA256(span)=f04c4ca87decfb4116f3fba64f937ecafc5b790d01ebd961ea2b3ee6a53bcfa6.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05315A)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x8E030020)
MUSASHI_NATIVE_MIPS_WORD(0x00022C03)
MUSASHI_NATIVE_MIPS_WORD(0x84640012)
MUSASHI_NATIVE_MIPS_WORD(0x0C004AC1)
MUSASHI_NATIVE_MIPS_WORD(0x24060004)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x8E050020)
MUSASHI_NATIVE_MIPS_WORD(0x00041400)
MUSASHI_NATIVE_MIPS_WORD(0x94A30012)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0x30630FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4A30012)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s16 func_80012B04(s16, s16, s32);               /* extern */
s16 func_8014C568();                                /* static */

s16 func_80171AB0(void *arg0) {
    s16 temp_v0;
    void *temp_a1;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), func_8014C568(), 4);
    temp_a1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a1, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a1, s16 *, 0x12) + temp_v0) & 0xFFF);
    return temp_v0;
}
#endif
