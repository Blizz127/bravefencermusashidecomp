/* Main-exec range [8002A1B4,8002A200) from the SLUS executable.
 * SHA256(span)=85447d38de075cb556948414a0a0b8175c0f800933e33c289858910506f02151.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A89B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA80)
MUSASHI_NATIVE_MIPS_WORD(0x24440001)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A89F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A8A3)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x02028026)
MUSASHI_NATIVE_MIPS_WORD(0x2E020001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
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

s32 func_8002A26C();                                /* static */
s32 func_8002A27C();                                /* static */
s32 func_8002A28C();                                /* static */
s32 func_8002AA00(s32);                             /* static */

s32 func_8002A1B4(void) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = 0;
    if (func_8002AA00(func_8002A26C() + 1) != 0) {
        temp_s0 = func_8002A27C();
        var_v0 = temp_s0 == func_8002A28C();
    }
    return var_v0;
}
#endif
