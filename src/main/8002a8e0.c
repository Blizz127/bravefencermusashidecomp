/* Main-exec range [8002A8E0,8002A92C) from the SLUS executable.
 * SHA256(span)=a77e0c7ab6571ca18f7736c988f866af351a915b68654226040dcf59cbb120d4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA66)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA80)
MUSASHI_NATIVE_MIPS_WORD(0x24440001)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA6A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA6E)
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

s32 func_8002A998();                                /* static */
s32 func_8002A9A8();                                /* static */
s32 func_8002A9B8();                                /* static */
s32 func_8002AA00(s32);                             /* static */

s32 func_8002A8E0(void) {
    s32 temp_s0;
    s32 var_v0;

    var_v0 = 0;
    if (func_8002AA00(func_8002A998() + 1) != 0) {
        temp_s0 = func_8002A9A8();
        var_v0 = temp_s0 == func_8002A9B8();
    }
    return var_v0;
}
#endif
