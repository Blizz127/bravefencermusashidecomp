/* Main-exec range [8003CF68,8003CFF8) from the SLUS executable.
 * SHA256(span)=a5ee5da0f80f5cf64408b981436a6907dd58464eea7346a124ad29914483de5f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x2403103B)
MUSASHI_NATIVE_MIPS_WORD(0x00830018)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF0)
MUSASHI_NATIVE_MIPS_WORD(0x00044300)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00053942)
MUSASHI_NATIVE_MIPS_WORD(0x30A5001F)
MUSASHI_NATIVE_MIPS_WORD(0x00004812)
MUSASHI_NATIVE_MIPS_WORD(0x10E00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFA90008)
MUSASHI_NATIVE_MIPS_WORD(0x00830018)
MUSASHI_NATIVE_MIPS_WORD(0x00031180)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00021100)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00004012)
MUSASHI_NATIVE_MIPS_WORD(0x00431823)
MUSASHI_NATIVE_MIPS_WORD(0x00031B02)
MUSASHI_NATIVE_MIPS_WORD(0x00830018)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x00C7102A)
MUSASHI_NATIVE_MIPS_WORD(0x00004812)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF3)
MUSASHI_NATIVE_MIPS_WORD(0xAFA90008)
MUSASHI_NATIVE_MIPS_WORD(0x8FA90008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x01281023)
MUSASHI_NATIVE_MIPS_WORD(0x00021142)
MUSASHI_NATIVE_MIPS_WORD(0x00450018)
MUSASHI_NATIVE_MIPS_WORD(0x00004812)
MUSASHI_NATIVE_MIPS_WORD(0x01091021)
MUSASHI_NATIVE_MIPS_WORD(0x00021302)
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

u32 func_8003CF68(s32 arg0, u32 arg1) {
    s32 sp8;
    s32 var_a2;
    s32 var_lo;
    s32 var_t0;
    u32 temp_a3;
    u32 var_v1;

    var_v1 = 0x103B;
    var_t0 = arg0 << 0xC;
    var_a2 = 0;
    temp_a3 = arg1 >> 5;
    sp8 = arg0 * 0x103B;
    if (temp_a3 != 0) {
        var_lo = arg0 * 0x103B;
        do {
            var_t0 = var_lo;
            var_v1 = (u32) (var_v1 * 0x103B) >> 0xC;
            var_lo = arg0 * var_v1;
            var_a2 += 1;
            sp8 = var_lo;
        } while (var_a2 < (s32) temp_a3);
    }
    return (u32) (var_t0 + (((u32) (sp8 - var_t0) >> 5) * (arg1 & 0x1F))) >> 0xC;
}
#endif
