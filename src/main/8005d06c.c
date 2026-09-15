/* Main-exec range [8005D06C,8005D0A0) from the SLUS executable.
 * SHA256(span)=9ed85bbaad6c53fd624661402474b3d4b4ae3ecd7842807893e09c18d1b26b67.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3084FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00042080)
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA52934)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x8C42293C)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30004)
MUSASHI_NATIVE_MIPS_WORD(0x00021027)
MUSASHI_NATIVE_MIPS_WORD(0x00621824)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
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

s32 func_8005D06C(s32 arg0) {
    M2C_FIELD(D_80072934, s32 *, 4) = (s32) (M2C_FIELD(D_80072934, s32 *, 4) & ~*(func_8007293C + ((arg0 & 0xFFFF) * 4)));
    return 1;
}
#endif
