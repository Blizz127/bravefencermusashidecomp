/* Exact retail word export for [80034B0C,80034B3C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03800A)
MUSASHI_NATIVE_MIPS_WORD(0x24634F17)
MUSASHI_NATIVE_MIPS_WORD(0x90650000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA0620000)
MUSASHI_NATIVE_MIPS_WORD(0xA082002A)
MUSASHI_NATIVE_MIPS_WORD(0x240203FF)
MUSASHI_NATIVE_MIPS_WORD(0xA4820026)
MUSASHI_NATIVE_MIPS_WORD(0x24023FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4820028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0650000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 D_800A4F17;

void func_80034B0C(void *arg0) {
    u8 temp_a1;

    temp_a1 = D_800A4F17;
    D_800A4F17 = 1;
    M2C_FIELD(arg0, s8 *, 0x2A) = 1;
    M2C_FIELD(arg0, s16 *, 0x26) = 0x3FF;
    M2C_FIELD(arg0, s16 *, 0x28) = 0x3FFF;
    D_800A4F17 = temp_a1;
}
#endif
