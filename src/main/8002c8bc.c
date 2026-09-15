/* Exact retail word export for [8002C8BC,8002C8F4); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x2404ffff)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0xa4245328)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0xa424532a)
MUSASHI_NATIVE_MIPS_WORD(0x24630004)
MUSASHI_NATIVE_MIPS_WORD(0x2c6201e4)
MUSASHI_NATIVE_MIPS_WORD(0x1440fff7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_800C5328;
extern s32 *D_800C532A;

void func_8002C8BC(void) {
    u32 var_v1;

    var_v1 = 0;
    do {
        *(&D_800C5328 + var_v1) = -1;
        *(&D_800C532A + var_v1) = -1;
        var_v1 += 4;
    } while (var_v1 < 0x1E4U);
}
#endif
