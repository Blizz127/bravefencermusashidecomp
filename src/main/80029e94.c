/* Main-exec range [80029E94,80029EC0) from the SLUS executable.
 * SHA256(span)=3a3831b8b774d0e0ea7e820ff61123b177d704dadd0617838da9c0317045ced6.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C820078)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84430030)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10600004)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x00650018)
MUSASHI_NATIVE_MIPS_WORD(0x00003012)
MUSASHI_NATIVE_MIPS_WORD(0x00061303)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80029E94(void *arg0, s32 arg1) {
    s16 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x78), s16 *, 0x30);
    var_v0 = 0;
    if (temp_v1 != 0) {
        var_v0 = (s32) (temp_v1 * arg1) >> 0xC;
    }
    return var_v0;
}
#endif
