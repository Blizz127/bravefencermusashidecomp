/* Overlay range [8014C118,8014C168) from MAIN.CD member 0012.
 * SHA256(span)=914cdf0e3c0a33b38a643a7c03e21084ee6563c116939ae35a623c9198a40a16.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x00063403)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x246302A0)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14450005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84620070)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10460006)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2C820060)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF5)
MUSASHI_NATIVE_MIPS_WORD(0x2463010C)
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

extern s32 *D_801202A0;

void *func_8014C118(s32 arg1, s16 arg2) {
    void *var_v0;
    void *var_v1;
    u32 var_a0;

    var_a0 = 0;
    var_v1 = &D_801202A0;
loop_1:
    if ((M2C_FIELD(var_v1, u16 *, 0) != arg1) || (var_v0 = var_v1, (M2C_FIELD(var_v1, s16 *, 0x70) != arg2))) {
        var_a0 += 1;
        var_v1 += 0x10C;
        if (var_a0 >= 0x60U) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
#endif
