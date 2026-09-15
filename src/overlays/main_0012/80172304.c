/* Overlay range [80172304,80172310) from MAIN.CD member 0012.
 * SHA256(span)=dd9857ae69a334278a7c558c0e2c70f390057b267078a5afe7ed980f457df472.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020040)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48200AA)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80172304(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xAA) = 0x40;
}
#endif
