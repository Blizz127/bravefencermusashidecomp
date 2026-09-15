/* Overlay range [80146924,80146994) from MAIN.CD member 0012.
 * SHA256(span)=630377113f611dff15c5a153e78e8932795531eaf951a27197fe9b678ffa718f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x2463D030)
MUSASHI_NATIVE_MIPS_WORD(0x246A0A50)
MUSASHI_NATIVE_MIPS_WORD(0x8FAB0028)
MUSASHI_NATIVE_MIPS_WORD(0x006A102B)
MUSASHI_NATIVE_MIPS_WORD(0x1040000B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3089FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14490002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x25080001)
MUSASHI_NATIVE_MIPS_WORD(0x24630058)
MUSASHI_NATIVE_MIPS_WORD(0x006A102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x010B102B)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051A65)
MUSASHI_NATIVE_MIPS_WORD(0x3084FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80146994(s32);                             /* static */
extern u16 D_8011D030;

s32 func_80146924(s32 arg0, u32 arg4) {
    s32 var_v0;
    u16 *temp_t2;
    u16 *var_v1;
    u32 var_t0;

    var_t0 = 0;
    var_v1 = &D_8011D030;
    temp_t2 = &D_8011D030 + 0xA50;
    if ((u32) &D_8011D030 < (u32) temp_t2) {
        do {
            if (*var_v1 == (arg0 & 0xFFFF)) {
                var_t0 += 1;
            }
            var_v1 += 0x58;
        } while ((u32) var_v1 < (u32) temp_t2);
    }
    var_v0 = 0;
    if (var_t0 < arg4) {
        var_v0 = func_80146994(arg0 & 0xFFFF);
    }
    return var_v0;
}
#endif
