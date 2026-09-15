/* Overlay range [801487F4,80148800) from MAIN.CD member 0012.
 * SHA256(span)=0730c842c8ffbb491068fd8eb814bb66fcfedb899a2449f5c452ae3324784730.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x948200AA)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

u16 func_801487F4(void *arg0) {
    return M2C_FIELD(arg0, u16 *, 0xAA);
}
#endif
