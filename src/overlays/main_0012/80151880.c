/* Overlay range [80151880,801518D8) from MAIN.CD member 0012.
 * SHA256(span)=409e7861711e23597305bc9195bf13eed0910e05bd8abd11cc4ca2a4d7ba7b47.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9484003E)
MUSASHI_NATIVE_MIPS_WORD(0x2402001B)
MUSASHI_NATIVE_MIPS_WORD(0x308300FF)
MUSASHI_NATIVE_MIPS_WORD(0x1062000D)
MUSASHI_NATIVE_MIPS_WORD(0x2402001C)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0x2402000F)
MUSASHI_NATIVE_MIPS_WORD(0x10620009)
MUSASHI_NATIVE_MIPS_WORD(0x24020010)
MUSASHI_NATIVE_MIPS_WORD(0x10620007)
MUSASHI_NATIVE_MIPS_WORD(0x2402000B)
MUSASHI_NATIVE_MIPS_WORD(0x14620003)
MUSASHI_NATIVE_MIPS_WORD(0x2402001F)
MUSASHI_NATIVE_MIPS_WORD(0x08054634)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x14620003)
MUSASHI_NATIVE_MIPS_WORD(0x00041202)
MUSASHI_NATIVE_MIPS_WORD(0x08054634)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x30420002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80151880(void *arg0) {
    s32 temp_v1;
    u16 temp_a0;

    temp_a0 = M2C_FIELD(arg0, u16 *, 0x3E);
    temp_v1 = temp_a0 & 0xFF;
    if ((temp_v1 != 0x1B) && (temp_v1 != 0x1C) && (temp_v1 != 0xF) && (temp_v1 != 0x10)) {
        if (temp_v1 == 0xB) {
            return 2;
        }
        if (temp_v1 == 0x1F) {
            goto block_7;
        }
        return (temp_a0 >> 8) & 2;
    }
block_7:
    return 1;
}
#endif
