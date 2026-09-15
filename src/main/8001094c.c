/* Main-exec range [8001094C,8001096C) from the SLUS executable.
 * SHA256(span)=4f333c8fc41b9063a42c85d18b5b1eca22b56a3d956ecbda8ee5ce4e09dce466.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0034)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0030)
MUSASHI_NATIVE_MIPS_WORD(0x8FB1002C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00028)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8001094C(void) {

}
#endif
