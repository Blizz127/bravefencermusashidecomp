/* Main-exec range [8002A400,8002A44C) from the SLUS executable.
 * SHA256(span)=78c807474851e67454d28c8407b51ac781f3597292dee959df26a07d2a6a586f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A92E)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA80)
MUSASHI_NATIVE_MIPS_WORD(0x24440001)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A932)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A936)
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

s32 func_8002A4B8();                                /* static */
s32 func_8002A4C8();                                /* static */
s32 func_8002A4D8();                                /* static */
s32 func_8002AA00(s32);                             /* static */

s32 func_8002A400(void) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = 0;
    if (func_8002AA00(func_8002A4B8() + 1) != 0) {
        temp_s0 = func_8002A4C8();
        var_v0 = temp_s0 == func_8002A4D8();
    }
    return var_v0;
}
#endif
