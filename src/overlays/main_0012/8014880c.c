/* Overlay range [8014880C,80148818) from MAIN.CD member 0012.
 * SHA256(span)=91ef235761715d5731cc5d02581c858d2f61babb0e4554fae8850e205192ccca.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908200AE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

u8 func_8014880C(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0xAE);
}
#endif
