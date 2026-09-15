/* Overlay range [80149210,80149228) from MAIN.CD member 0012.
 * SHA256(span)=971545ab5eafaf472a7b66c54b71ea6fd6a5880e9eb1c3573cab34719307ae9c.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00A21025)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201E4)
MUSASHI_NATIVE_MIPS_WORD(0xA48501E4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48501E6)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80149210(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s32 *, 0x1E4) = (s32) (arg1 | (arg1 << 0x10));
    M2C_FIELD(arg0, s32 *, 0x1E4) = arg1;
    M2C_FIELD(arg0, s16 *, 0x1E6) = arg1;
}
#endif
