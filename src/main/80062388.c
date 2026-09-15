/* Main-exec range [80062388,80062394) from the SLUS executable.
 * SHA256(span)=c28242c524b4002a079049d874fd1774d14c53808b23515f50cb9a0c4550529a.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC242A24)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 func_80072A24;

void func_80062388(s32 arg0) {
    func_80072A24 = arg0;
}
#endif
