/* Native retail instruction export [80058B04,80058B40).
 * Verified against asm/main.s and the extracted EXE. No C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8FA30010)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0xA4450000)
MUSASHI_NATIVE_MIPS_WORD(0xA4460002)
MUSASHI_NATIVE_MIPS_WORD(0xA4470004)
MUSASHI_NATIVE_MIPS_WORD(0xA4400008)
MUSASHI_NATIVE_MIPS_WORD(0xA440000A)
MUSASHI_NATIVE_MIPS_WORD(0xA440000C)
MUSASHI_NATIVE_MIPS_WORD(0xA440000E)
MUSASHI_NATIVE_MIPS_WORD(0xA0400011)
MUSASHI_NATIVE_MIPS_WORD(0xA0400010)
MUSASHI_NATIVE_MIPS_WORD(0xA0400013)
MUSASHI_NATIVE_MIPS_WORD(0xA0400012)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4430006)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80058B04(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    M2C_FIELD(arg0, s16 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 2) = arg2;
    M2C_FIELD(arg0, s16 *, 4) = arg3;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, s8 *, 0x13) = 0;
    M2C_FIELD(arg0, s8 *, 0x12) = 0;
    M2C_FIELD(arg0, s16 *, 6) = (s16) arg4;
}
#endif
