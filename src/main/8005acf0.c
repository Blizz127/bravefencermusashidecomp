/* Exact retail word export for [8005ACF0,8005AD34); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007)
MUSASHI_NATIVE_MIPS_WORD(0x90422788)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442ffff)
MUSASHI_NATIVE_MIPS_WORD(0x2c420002)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x30a30fff)
MUSASHI_NATIVE_MIPS_WORD(0x30a307ff)
MUSASHI_NATIVE_MIPS_WORD(0x00031ac0)
MUSASHI_NATIVE_MIPS_WORD(0x08016b49)
MUSASHI_NATIVE_MIPS_WORD(0x308207ff)
MUSASHI_NATIVE_MIPS_WORD(0x00031b00)
MUSASHI_NATIVE_MIPS_WORD(0x30820fff)
MUSASHI_NATIVE_MIPS_WORD(0x3c04e500)
MUSASHI_NATIVE_MIPS_WORD(0x00441025)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00621025)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80072788;
s32 func_8005ACF0(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v1;

    if ((u32) (D_80072788 - 1) >= 2U) {
        var_v1 = (arg1 & 0x7FF) << 0xB;
        var_v0 = arg0 & 0x7FF;
    } else {
        var_v1 = (arg1 & 0xFFF) << 0xC;
        var_v0 = arg0 & 0xFFF;
    }
    return var_v1 | (var_v0 | 0xE5000000);
}
#endif
