/* Overlay range [80156600,80156648) from MAIN.CD member 0012.
 * SHA256(span)=ab9145429a2387cd66af6d2d74ddc7b5befce9f1cdf07e2f7e138d4fc9644639.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x24A56AF0)
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x246351E0)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420001)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
MUSASHI_NATIVE_MIPS_WORD(0x24A50008)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2C820003)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF7)
MUSASHI_NATIVE_MIPS_WORD(0x24630004)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_801151E0;
extern s32 *D_80126AF0;

void *func_80156600(void) {
    void *var_a1;
    void *var_v0;
    s32 *var_v1;
    u32 var_a0;

    var_a0 = 0;
    var_a1 = &D_80126AF0;
    var_v1 = &D_801151E0;
loop_1:
    var_v0 = var_a1;
    if (!(*var_v1 & 1)) {
        var_a1 += 8;
        var_a0 += 1;
        var_v1 += 4;
        if (var_a0 >= 3U) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
#endif
