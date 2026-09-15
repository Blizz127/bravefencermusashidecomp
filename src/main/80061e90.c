/* Main-exec range [80061E90,80061F38) from the SLUS executable.
 * SHA256(span)=c99aa8e299b15f22b5abc73e92e087b82e26281f7be7c57554e3356126b5ffc8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00A09021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x1220001B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x1240001A)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C017346)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x02402021)
MUSASHI_NATIVE_MIPS_WORD(0x0C017346)
MUSASHI_NATIVE_MIPS_WORD(0x02228021)
MUSASHI_NATIVE_MIPS_WORD(0x02421021)
MUSASHI_NATIVE_MIPS_WORD(0x12020011)
MUSASHI_NATIVE_MIPS_WORD(0x02201821)
MUSASHI_NATIVE_MIPS_WORD(0x90620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x24710001)
MUSASHI_NATIVE_MIPS_WORD(0x92220000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x26310001)
MUSASHI_NATIVE_MIPS_WORD(0x2631FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x92420000)
MUSASHI_NATIVE_MIPS_WORD(0x26520001)
MUSASHI_NATIVE_MIPS_WORD(0xA2220000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x26310001)
MUSASHI_NATIVE_MIPS_WORD(0x080187C7)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
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

s32 func_8005CD18(u8 *);                            /* static */

u8 *func_80061E90(u8 *arg0, u8 *arg1) {
    u8 *temp_s0;
    u8 *var_s1;
    u8 *var_s1_2;
    u8 *var_s2;
    u8 temp_v0;

    var_s2 = arg1;
    if (arg0 != 0) {
        if (var_s2 != 0) {
            temp_s0 = &arg0[func_8005CD18(arg0)];
            if (temp_s0 != &var_s2[func_8005CD18(var_s2)]) {
                var_s1 = arg0 + 1;
                if (*arg0 != 0) {
                    do {
                        var_s1 += 1;
                    } while (*var_s1 != 0);
                }
                var_s1_2 = var_s1 - 1;
                do {
                    temp_v0 = *var_s2;
                    var_s2 += 1;
                    *var_s1_2 = temp_v0;
                    var_s1_2 += 1;
                } while (temp_v0 != 0);
                return arg0;
            }
            goto block_8;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 0;
    }
block_8:
    return 0;
}
#endif
