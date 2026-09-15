/* Exact retail word export [8002F658,8002F67C); verified against pinned EXE and asm. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800A)
MUSASHI_NATIVE_MIPS_WORD(0x90424698)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800A)
MUSASHI_NATIVE_MIPS_WORD(0x84424688)
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

extern s16 D_800A4688;
extern u8 D_800A4698;

s16 func_8002F658(void) {
    s16 var_v0;

    var_v0 = -1;
    if (D_800A4698 == 0) {
        var_v0 = D_800A4688;
    }
    return var_v0;
}
#endif
