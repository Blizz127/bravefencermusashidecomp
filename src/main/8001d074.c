/* Exact retail [8001D074,8001D0E8).
 * Words from pinned SLUS_007.26.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C07800B)
MUSASHI_NATIVE_MIPS_WORD(0x24E7F630)
MUSASHI_NATIVE_MIPS_WORD(0x2C820100)
MUSASHI_NATIVE_MIPS_WORD(0x10400016)
MUSASHI_NATIVE_MIPS_WORD(0x2CA20101)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0x0085102A)
MUSASHI_NATIVE_MIPS_WORD(0x08007438)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x24C265A8)
MUSASHI_NATIVE_MIPS_WORD(0x08007438)
MUSASHI_NATIVE_MIPS_WORD(0x00E21021)
MUSASHI_NATIVE_MIPS_WORD(0x1040000D)
MUSASHI_NATIVE_MIPS_WORD(0x000410C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x00471821)
MUSASHI_NATIVE_MIPS_WORD(0x00403021)
MUSASHI_NATIVE_MIPS_WORD(0x946265A8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x24630038)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x0085102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x24C60038)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_800AF630;

void *func_8001D074(u32 arg0, u32 arg1) {
    s32 temp_v0;
    s32 var_a2;
    u32 var_a0;
    void *var_v1;

    var_a0 = arg0;
    if (var_a0 < 0x100U) {
        if (arg1 >= 0x101U) {
            return 0;
        }
        if ((s32) var_a0 < (s32) arg1) {
            temp_v0 = var_a0 * 0x38;
            var_v1 = temp_v0 + &D_800AF630;
            var_a2 = temp_v0;
loop_6:
            var_v1 += 0x38;
            if (M2C_FIELD(var_v1, u16 *, 0x65A8) != 0) {
                var_a0 += 1;
                var_a2 += 0x38;
                if ((s32) var_a0 >= (s32) arg1) {
                    goto block_8;
                }
                goto loop_6;
            }
            return &D_800AF630 + (var_a2 + 0x65A8);
        }
        goto block_8;
    }
block_8:
    return 0;
}
#endif
