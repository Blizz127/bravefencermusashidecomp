/* Overlay range [80131CF4,80131D68) from MAIN.CD member 0012.
 * SHA256(span)=5e4fce9b9a54c616d357f19428c3cd2da6ee4cda625803d02ac3cfb394096c4b.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x14800006)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0804C758)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820004)
MUSASHI_NATIVE_MIPS_WORD(0x0804C758)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400011)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x2403000D)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14430004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C840004)
MUSASHI_NATIVE_MIPS_WORD(0x0804C753)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1045FFF0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24840008)
MUSASHI_NATIVE_MIPS_WORD(0x8C820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 *func_80131CF4(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 var_v0;

    var_a0 = arg0;
    if (var_a0 == 0) {
        return 0;
    }
    if (*var_a0 != 0) {
        var_v0 = *var_a0;
loop_5:
        if (var_v0 == 0xD) {
            var_a0 = M2C_FIELD(var_a0, s32 **, 4);
            goto block_9;
        }
        if (var_v0 != arg1) {
            var_a0 += 8;
block_9:
            var_v0 = *var_a0;
            if (var_v0 == 0) {
                /* Duplicate return node #11. Try simplifying control flow for better match */
                return 0;
            }
            goto loop_5;
        }
        return M2C_FIELD(var_a0, s32 **, 4);
    }
    return 0;
}
#endif
