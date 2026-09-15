/* Exact retail word export for [8003836C,800383A4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000411C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021880)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90229ED3)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90229ED2)
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

extern s32 *D_800B9ED2;
extern s32 *D_800B9ED3;

u8 func_8003836C(s32 arg0) {
    s32 temp_v1;
    u8 var_v0;

    temp_v1 = arg0 * 0x1FC;
    var_v0 = 0;
    if (*(&D_800B9ED3 + temp_v1) != 0) {
        var_v0 = *(&D_800B9ED2 + temp_v1);
    }
    return var_v0;
}
#endif
