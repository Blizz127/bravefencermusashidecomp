/* Main-exec range [8005D03C,8005D06C) from the SLUS executable.
 * SHA256(span)=bb6378fe66c0db8f1ba74ad75ac1dcb69cb07d980291d12dba71feab3d076e62.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3082FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00022080)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA52934)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x00240821)
MUSASHI_NATIVE_MIPS_WORD(0x8C24293C)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30004)
MUSASHI_NATIVE_MIPS_WORD(0x28420003)
MUSASHI_NATIVE_MIPS_WORD(0x00641825)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACA30004)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80072934;
extern s32 func_8007293C[];

s32 func_8005D03C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = arg0 & 0xFFFF;
    M2C_FIELD(D_80072934, s32 *, 4) = (s32) (M2C_FIELD(D_80072934, s32 *, 4) | *(func_8007293C + (temp_v0 * 4)));
    return temp_v0 < 3;
}
#endif
