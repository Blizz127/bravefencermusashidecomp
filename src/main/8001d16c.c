/* Main-exec range [8001D16C,8001D1C4) from the SLUS executable.
 * SHA256(span)=07a7d66d7d42659079c63e4d11282fbcbbe6966f62f8660d72a4552ef38a2387.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0380FF)
MUSASHI_NATIVE_MIPS_WORD(0x8C820080)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x10400009)
MUSASHI_NATIVE_MIPS_WORD(0x24860080)
MUSASHI_NATIVE_MIPS_WORD(0x3C0380FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00C33024)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C0280FF)
MUSASHI_NATIVE_MIPS_WORD(0x3442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00A21024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030100)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xACC20000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACA00000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8001D16C(void *arg0, s32 arg1) {
    s32 *var_a2;

    var_a2 = arg0 + 0x80;
    if (arg0->unk80 & 0x80FFFFFF) {
        do {
            var_a2 = (s32 *) ((s32) var_a2 & 0x80FFFFFF);
        } while (*var_a2 & 0x80FFFFFF);
    }
    *var_a2 = (arg1 & 0x80FFFFFF) | 0x01000000;
    *arg1 = 0;
}
#endif
