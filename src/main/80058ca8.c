/* Main-exec range [80058CA8,80058CE4) from the SLUS executable.
 * SHA256(span)=b8f4360e6e689e8860897359cf6e98bab5eaba5e11b218cb5637492c1875b33c.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0700FF)
MUSASHI_NATIVE_MIPS_WORD(0x34E7FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C08FF00)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00681824)
MUSASHI_NATIVE_MIPS_WORD(0x00471024)
MUSASHI_NATIVE_MIPS_WORD(0x00621825)
MUSASHI_NATIVE_MIPS_WORD(0xACC30000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00A72824)
MUSASHI_NATIVE_MIPS_WORD(0x00481024)
MUSASHI_NATIVE_MIPS_WORD(0x00451025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80058CA8(s32 *arg0, s32 arg1, s32 *arg2) {
    *arg2 = (*arg2 & 0xFF000000) | (*arg0 & 0xFFFFFF);
    *arg0 = (*arg0 & 0xFF000000) | (arg1 & 0xFFFFFF);
}
#endif
