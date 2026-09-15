/* Overlay range [8014A69C,8014A6A8) from MAIN.CD member 0012.
 * SHA256(span)=58c8b16bd96335e68eed5040c3cbbb0282746ea315022b6bd72d9656b6f925c8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908201BD)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8014A69C(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x1BD) == 0;
}
#endif
