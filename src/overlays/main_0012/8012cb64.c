/* Overlay range [8012CB64,8012CBA4) from MAIN.CD member 0012.
 * SHA256(span)=7473d57666284aac10e2e0d3e80cb3ece9fdc897d8441a12a5066d45ec2a64c8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84830000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA80010)
MUSASHI_NATIVE_MIPS_WORD(0x0065282A)
MUSASHI_NATIVE_MIPS_WORD(0x14A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0066182A)
MUSASHI_NATIVE_MIPS_WORD(0x10600007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84840004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0087182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0088102A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8012CB64(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s16 temp_a0;
    s16 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    var_v0 = 0;
    if ((temp_v1 >= arg1) && (temp_v1 < arg2)) {
        temp_a0 = M2C_FIELD(arg0, s16 *, 4);
        if (temp_a0 >= arg3) {
            var_v0 = temp_a0 < arg4;
        }
    }
    return var_v0;
}
#endif
