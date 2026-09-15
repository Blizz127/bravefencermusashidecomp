/* Overlay range [8012BEE8,8012BF10) from MAIN.CD member 0012.
 * SHA256(span)=a8522550f2955788083bc1ea26b1c6627bb07a529fa079e38588b9aa9f5fa3f6.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C82001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0804AFC2)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8012BEE8(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x1C);
    temp_v0 = temp_v0_2 - 1;
    if (temp_v0_2 == 0) {
        return 1;
    }
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v0;
    return temp_v0 == 0;
}
#endif
