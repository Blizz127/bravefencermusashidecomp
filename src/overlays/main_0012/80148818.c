/* Overlay range [80148818,80148824) from MAIN.CD member 0012.
 * SHA256(span)=4bbd36ec046bfd27d7006868faa918f9666ff411e0ea0d600e0feacaa8de69ad.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x948200AE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00021202)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

u32 func_80148818(void *arg0) {
    return (u16) M2C_FIELD(arg0, u16 *, 0xAE) >> 8;
}
#endif
