/* Overlay range [8014A674,8014A680) from MAIN.CD member 0012.
 * SHA256(span)=64fe22129c384365941dacc8aca665386472b50b6ae1422e5f5cae0f54f49a20.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908201BC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8014A674(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x1BC) == 0;
}
#endif
