/* Overlay range [801585A4,801585AC) from MAIN.CD member 0012.
 * SHA256(span)=8451a7d78b2ed8a467bb5aa6b1d3074d330862a5cedaa3963c0d4a9c3f72167e.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4800244)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_801585A4(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x244) = 0;
}
#endif
