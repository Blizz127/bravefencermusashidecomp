/* Main-exec range [8005D0A0,8005D0D4) from the SLUS executable.
 * SHA256(span)=5bd7e39d766d33d5d022a06018938f7bbdd8be8a949541884f5a0a8cb15a6505.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3083FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x28620003)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x8C842938)
MUSASHI_NATIVE_MIPS_WORD(0x00031900)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0x08017433)
MUSASHI_NATIVE_MIPS_WORD(0xA4600000)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80072938;

s32 func_8005D0A0(s32 arg0) {
    s32 temp_v1;

    temp_v1 = arg0 & 0xFFFF;
    if (temp_v1 < 3) {
        *((temp_v1 * 0x10) + D_80072938) = 0;
        return 1;
    }
    return 0;
}
#endif
