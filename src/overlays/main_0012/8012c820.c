/* Overlay range [8012C820,8012C890) from MAIN.CD member 0012.
 * SHA256(span)=9afdf98da44754df35af4b84593410e22aa0ec9c759195af15cfbc626f517241.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24630194)
MUSASHI_NATIVE_MIPS_WORD(0x24656480)
MUSASHI_NATIVE_MIPS_WORD(0x10A30008)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FEF4)
MUSASHI_NATIVE_MIPS_WORD(0x14A3FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x10A00008)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34428000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B224)
MUSASHI_NATIVE_MIPS_WORD(0xA482000A)
MUSASHI_NATIVE_MIPS_WORD(0x0804B220)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8012C890(u16 *, s32);                  /* static */
extern s32 *D_80120194;

s32 func_8012C820(void *arg0) {
    u16 *var_a1;

    var_a1 = &D_80120194 + 0x6480;
    if (var_a1 != &D_80120194) {
loop_1:
        if (*var_a1 != 0) {
            var_a1 -= 0x10C;
            if (var_a1 == &D_80120194) {
                goto block_3;
            }
            goto loop_1;
        }
    } else {
block_3:
        var_a1 = 0;
    }
    if (var_a1 != 0) {
        M2C_FIELD(arg0, u16 *, 0xA) = (u16) (M2C_FIELD(arg0, u16 *, 0xA) | 0x8000);
        return func_8012C890(var_a1, 0);
    }
    return 0;
}
#endif
