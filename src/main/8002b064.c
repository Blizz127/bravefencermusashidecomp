/* Main-exec range [8002B064,8002B08C) from the SLUS executable.
 * SHA256(span)=afb0ccaa0539af38b3c679a5abb12a1a446c9abccee0ce6f0753d5ff41431b76.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x24850070)
MUSASHI_NATIVE_MIPS_WORD(0x90820000)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x0085102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x3062FFFF)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8002B064(u8 *arg0) {
    s32 temp_a1;
    s32 var_v1;
    u8 *var_a0;
    s32 temp_v0;

    var_a0 = arg0;
    var_v1 = 0;
    temp_a1 = var_a0 + 0x70;
    do {
        temp_v0 = *var_a0;
        var_a0 += 1;
        var_v1 += temp_v0;
    } while ((s32) var_a0 < temp_a1);
    return var_v1 & 0xFFFF;
}
#endif
