/* Overlay range [801490E8,801490F0) from MAIN.CD member 0012.
 * SHA256(span)=b7d46bd7cd17de3236fc35b140d5de08d9d5b406537aa97ae4c5cece6c4da787.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA485010A)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_801490E8(void *arg0, s16 arg1) {
    M2C_FIELD(arg0, s16 *, 0x10A) = arg1;
}
#endif
