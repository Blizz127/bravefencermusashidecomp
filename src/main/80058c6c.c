/* Main-exec range [80058C6C,80058CA8) from the SLUS executable.
 * SHA256(span)=1c2e33c9e0ddfcd56385916112089fab3d7d343336e2514633a70260ef7d4064.
 * Word export only: the native seam executes the retail instruction
 * stream itself; this is not a C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0600FF)
MUSASHI_NATIVE_MIPS_WORD(0x34C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C07FF00)
MUSASHI_NATIVE_MIPS_WORD(0x8CA30000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00671824)
MUSASHI_NATIVE_MIPS_WORD(0x00461024)
MUSASHI_NATIVE_MIPS_WORD(0x00621825)
MUSASHI_NATIVE_MIPS_WORD(0xACA30000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00A62824)
MUSASHI_NATIVE_MIPS_WORD(0x00471024)
MUSASHI_NATIVE_MIPS_WORD(0x00451025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80058C6C(s32 *arg0, s32 *arg1) {
    *arg1 = (*arg1 & 0xFF000000) | (*arg0 & 0xFFFFFF);
    *arg0 = (*arg0 & 0xFF000000) | ((s32) arg1 & 0xFFFFFF);
}
#endif
