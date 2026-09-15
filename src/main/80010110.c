/* Main-exec range [80010110,80010178) from the SLUS executable.
 * SHA256(span)=422b7e8743ae79493a90d8582626284dcfb0df9651369976f7ad57a8a8c9672e.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C088006)
MUSASHI_NATIVE_MIPS_WORD(0x8D082998)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00004)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10008)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF000C)
MUSASHI_NATIVE_MIPS_WORD(0x1100000D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C108001)
MUSASHI_NATIVE_MIPS_WORD(0x26100000)
MUSASHI_NATIVE_MIPS_WORD(0x3C110000)
MUSASHI_NATIVE_MIPS_WORD(0x26310000)
MUSASHI_NATIVE_MIPS_WORD(0x12200007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8E080000)
MUSASHI_NATIVE_MIPS_WORD(0x26100004)
MUSASHI_NATIVE_MIPS_WORD(0x0100F809)
MUSASHI_NATIVE_MIPS_WORD(0x2631FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1620FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF000C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10008)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00004)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0010)
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

extern s32 D_80062998;
extern s32 func_80010000;

void func_80010110(void) {
    s32 (*temp_t0)();
    s32 (*var_s0)();
    s32 var_s1;

    if (D_80062998 != 0) {
        var_s0 = func_80010000;
        var_s1 = 0;
        if (0 != 0) {
            do {
                temp_t0 = *var_s0;
                var_s0 += 4;
                var_s1 -= 1;
                temp_t0();
            } while (var_s1 != 0);
        }
    }
}
#endif
