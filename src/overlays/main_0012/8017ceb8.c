/* Overlay range [8017CEB8,8017CF3C) from MAIN.CD member 0012.
 * SHA256(span)=5db86f8dbba23722320af2967b4803f7f4c86e91f2e3ae7fa7c0361ba93361b8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C030080)
MUSASHI_NATIVE_MIPS_WORD(0x34638080)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x000633C3)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20010)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0xAC430000)
MUSASHI_NATIVE_MIPS_WORD(0x28A20005)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0x00260821)
MUSASHI_NATIVE_MIPS_WORD(0x90265158)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x1CA00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0805F3C6)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x24020005)
MUSASHI_NATIVE_MIPS_WORD(0x10A20009)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00021C03)
MUSASHI_NATIVE_MIPS_WORD(0x0066102A)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00031080)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x8C480000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x01001021)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80115158;

s32 func_8017CEB8(s32 arg0, s16 arg1, s32 arg2, s32 arg3, s32 *arg4) {
    s32 temp_v1;
    s32 var_t0;
    s32 var_v0;

    *arg4 = 0x808080;
    var_t0 = 0;
    if (arg1 < 5) {
        if (arg1 <= 0) {
            if (arg1 != 0) {
                var_v0 = arg3 << 0x10;
                goto block_6;
            }
        } else {
            goto block_5;
        }
    } else if (arg1 != 5) {
block_5:
        var_v0 = arg3 << 0x10;
block_6:
        temp_v1 = var_v0 >> 0x10;
        if (temp_v1 < (s32) *(&D_80115158 + ((s32) (arg2 << 0x10) >> 0xF))) {
            var_t0 = *((temp_v1 * 4) + arg0);
        }
    }
    return var_t0;
}
#endif
