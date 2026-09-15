/* Exact retail word export for [8005C358,8005C388); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x10800009)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x1CC00003)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x080170E0)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0xA0850000)
MUSASHI_NATIVE_MIPS_WORD(0x24C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x1CC0FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
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

s8 *func_8005C358(s8 *arg0, s8 arg1, s32 arg2) {
    s32 var_a2;
    s8 *var_a0;
    s8 *var_v0;

    var_a0 = arg0;
    var_a2 = arg2;
    var_v0 = 0;
    if (var_a0 != 0) {
        var_v0 = var_a0;
        if (var_a2 <= 0) {
            return 0;
        }
        do {
            *var_a0 = arg1;
            var_a2 -= 1;
            var_a0 += 1;
        } while (var_a2 > 0);
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#endif
