/* Overlay range [80149E94,80149F2C) from MAIN.CD member 0012.
 * SHA256(span)=d330357cc69b701bc3176ce7308884c80b10aaaedeae83f6a8d450c55aeaf2eb.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x0C05BC6B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x14400017)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x922201C5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400013)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x261002A0)
MUSASHI_NATIVE_MIPS_WORD(0x26036480)
MUSASHI_NATIVE_MIPS_WORD(0x0203102B)
MUSASHI_NATIVE_MIPS_WORD(0x1040000C)
MUSASHI_NATIVE_MIPS_WORD(0xA22001C5)
MUSASHI_NATIVE_MIPS_WORD(0x00609021)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0527CB)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x2610010C)
MUSASHI_NATIVE_MIPS_WORD(0x080527C4)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0212102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80149F2C(void *, u32);                     /* static */
s32 func_8016F1AC();                                /* static */
extern s32 *D_801202A0;

s32 func_80149E94(void *arg0) {
    void *var_s0;
    void *temp_v1;

    if ((func_8016F1AC() == 0) && (M2C_FIELD(arg0, u8 *, 0x1C5) != 0)) {
        var_s0 = &D_801202A0;
        temp_v1 = &D_801202A0 + 0x6480;
        M2C_FIELD(arg0, u8 *, 0x1C5) = 0U;
        if ((u32) &D_801202A0 < (u32) temp_v1) {
loop_4:
            var_s0 += 0x10C;
            if (func_80149F2C(arg0, (u32) var_s0) != 0) {
                return 1;
            }
            if ((u32) var_s0 >= (u32) temp_v1) {
                goto block_7;
            }
            goto loop_4;
        }
block_7:
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
#endif
