/* Overlay range [8015115C,80151164) from MAIN.CD member 0012.
 * SHA256(span)=dd1f053be91e01c9de239f9f3cf1c80f0194b162f61bf52d1f2c0b4615919f33.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA485016C)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8015115C(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x16C) = arg1;
}
#endif
