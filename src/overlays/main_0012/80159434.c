/* Overlay range [80159434,80159464) from MAIN.CD member 0012.
 * SHA256(span)=90a64e64f9db3b9293471de43c26cbf106a860587a1eec901f61965463738e39.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C860020)
MUSASHI_NATIVE_MIPS_WORD(0x9483023A)
MUSASHI_NATIVE_MIPS_WORD(0x94C20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x30420FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4C20010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820238)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820238)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80159434(void *arg0, s32 arg1) {
    void *temp_a2;

    temp_a2 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a2, u16 *, 0x10) = (u16) ((M2C_FIELD(temp_a2, u16 *, 0x10) - M2C_FIELD(arg0, u16 *, 0x23A)) & 0xFFF);
    M2C_FIELD(arg0, s32 *, 0x238) = (s32) (M2C_FIELD(arg0, s32 *, 0x238) + arg1);
}
#endif
