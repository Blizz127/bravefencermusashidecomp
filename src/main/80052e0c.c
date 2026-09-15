/* Main-exec range [80052E0C,80052E38) from the SLUS executable.
 * SHA256(span)=3980fa7392d682d613a4a3505f88176340e437e5d3b35727768af8e8d6c4976f.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xA4800014)
MUSASHI_NATIVE_MIPS_WORD(0xA4800012)
MUSASHI_NATIVE_MIPS_WORD(0xA4800010)
MUSASHI_NATIVE_MIPS_WORD(0xAC820008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0xAC800020)
MUSASHI_NATIVE_MIPS_WORD(0xAC80001C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800018)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80052E0C(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    M2C_FIELD(arg0, s16 *, 0x12) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0x1000;
    M2C_FIELD(arg0, s32 *, 4) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}
#endif
