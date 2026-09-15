/* Main-exec range [8003B02C,8003B08C) from the SLUS executable.
 * SHA256(span)=6be9a3427b222c65b68d5e98c9ec9ba08efe9a514edddbd5c6e43fcede474242.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA5B55C)
MUSASHI_NATIVE_MIPS_WORD(0x3C03FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20000)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0xACA20000)
MUSASHI_NATIVE_MIPS_WORD(0x10800007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B55C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C430000)
MUSASHI_NATIVE_MIPS_WORD(0x0800EC1F)
MUSASHI_NATIVE_MIPS_WORD(0x3C040003)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B55C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C430000)
MUSASHI_NATIVE_MIPS_WORD(0x3C040005)
MUSASHI_NATIVE_MIPS_WORD(0x00641825)
MUSASHI_NATIVE_MIPS_WORD(0xAC430000)
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

extern s32 *D_8006B55C;

void func_8003B02C(s32 arg0) {
    s32 var_a0;
    s32 var_v1;

    *D_8006B55C &= 0xFFF8FFFF;
    if (arg0 != 0) {
        var_v1 = *D_8006B55C;
        var_a0 = 0x30000;
    } else {
        var_v1 = *D_8006B55C;
        var_a0 = 0x50000;
    }
    *D_8006B55C = var_v1 | var_a0;
}
#endif
