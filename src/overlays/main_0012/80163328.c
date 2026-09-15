/* Overlay range [80163328,801633A8) from MAIN.CD member 0012.
 * SHA256(span)=2f7f30733400879be4c0933bd8d062320c830c9bbb39deb88de7b52f3c21f66d.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00005021)
MUSASHI_NATIVE_MIPS_WORD(0x3C078011)
MUSASHI_NATIVE_MIPS_WORD(0x24E75100)
MUSASHI_NATIVE_MIPS_WORD(0x3C098012)
MUSASHI_NATIVE_MIPS_WORD(0x25296B18)
MUSASHI_NATIVE_MIPS_WORD(0x3C088011)
MUSASHI_NATIVE_MIPS_WORD(0x25085200)
MUSASHI_NATIVE_MIPS_WORD(0x8D020000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420001)
MUSASHI_NATIVE_MIPS_WORD(0x1040000D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8CE20000)
MUSASHI_NATIVE_MIPS_WORD(0x89230003)
MUSASHI_NATIVE_MIPS_WORD(0x99230000)
MUSASHI_NATIVE_MIPS_WORD(0x89240007)
MUSASHI_NATIVE_MIPS_WORD(0x99240004)
MUSASHI_NATIVE_MIPS_WORD(0xA843007F)
MUSASHI_NATIVE_MIPS_WORD(0xB843007C)
MUSASHI_NATIVE_MIPS_WORD(0xA8440083)
MUSASHI_NATIVE_MIPS_WORD(0xB8440080)
MUSASHI_NATIVE_MIPS_WORD(0x8CE20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4400082)
MUSASHI_NATIVE_MIPS_WORD(0x24E70004)
MUSASHI_NATIVE_MIPS_WORD(0x25290008)
MUSASHI_NATIVE_MIPS_WORD(0x254A0001)
MUSASHI_NATIVE_MIPS_WORD(0x2D420003)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEA)
MUSASHI_NATIVE_MIPS_WORD(0x25080004)
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

extern void *D_80115100;
extern s32 *D_80115200;

void func_80163328(void) {
    s32 *var_t0;
    u32 var_t2;
    void **var_a3;
    void *temp_v0;

    var_t2 = 0;
    var_a3 = &D_80115100;
    var_t0 = &D_80115200;
    do {
        if (*var_t0 & 1) {
            temp_v0 = *var_a3;
            temp_v0->unk7F = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
            temp_v0->unk83 = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
            (*var_a3)->unk82 = 0;
        }
        var_a3 += 4;
        var_t2 += 1;
        var_t0 += 4;
    } while (var_t2 < 3U);
}
#endif
