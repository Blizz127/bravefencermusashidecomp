/* Overlay range [80171A80,80171A88) from MAIN.CD member 0012.
 * SHA256(span)=1cf12c5f8a8264313490fdbc1518114525ae0a112766a6d4351653bdbbb20409.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC850200)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80171A80(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x200) = arg1;
}
#endif
