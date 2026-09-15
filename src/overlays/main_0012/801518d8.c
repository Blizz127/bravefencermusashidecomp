/* Overlay range [801518D8,80151924) from MAIN.CD member 0012.
 * SHA256(span)=77393231992d0f9820e76ebc707139d83f4090f54db5349d5d5041394acec2c8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9083003E)
MUSASHI_NATIVE_MIPS_WORD(0x2402001B)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0x2402001C)
MUSASHI_NATIVE_MIPS_WORD(0x10620009)
MUSASHI_NATIVE_MIPS_WORD(0x2402000F)
MUSASHI_NATIVE_MIPS_WORD(0x10620007)
MUSASHI_NATIVE_MIPS_WORD(0x24020010)
MUSASHI_NATIVE_MIPS_WORD(0x10620005)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0x10620003)
MUSASHI_NATIVE_MIPS_WORD(0x24020013)
MUSASHI_NATIVE_MIPS_WORD(0x14620003)
MUSASHI_NATIVE_MIPS_WORD(0x38620017)
MUSASHI_NATIVE_MIPS_WORD(0x08054647)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
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

s32 func_801518D8(void *arg0) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x3E);
    if ((temp_v1 == 0x1B) || (temp_v1 == 0x1C) || (temp_v1 == 0xF) || (temp_v1 == 0x10) || (temp_v1 == 3) || (temp_v1 == 0x13)) {
        return 1;
    }
    return temp_v1 == 0x17;
}
#endif
