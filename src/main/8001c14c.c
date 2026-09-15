/* Main-exec range [8001C14C,8001C1E4) from the SLUS executable.
 * SHA256(span)=51c5bfb6e4cc0e1887bff6cce570eaf306259298d87d20368ab93cf1c10a64e4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x3C11800B)
MUSASHI_NATIVE_MIPS_WORD(0x2631F630)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x263065A8)
MUSASHI_NATIVE_MIPS_WORD(0x26236688)
MUSASHI_NATIVE_MIPS_WORD(0x0203102B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x10400009)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00609021)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050038)
MUSASHI_NATIVE_MIPS_WORD(0x26100038)
MUSASHI_NATIVE_MIPS_WORD(0x0212102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x263002A8)
MUSASHI_NATIVE_MIPS_WORD(0x262304B8)
MUSASHI_NATIVE_MIPS_WORD(0x0203102B)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x00608821)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059C5)
MUSASHI_NATIVE_MIPS_WORD(0x24050084)
MUSASHI_NATIVE_MIPS_WORD(0x26100084)
MUSASHI_NATIVE_MIPS_WORD(0x0211102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
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

void func_80016714(u32, s32);                            /* static */
extern s32 *D_800AF630;

void func_8001C14C(void) {
    void *temp_v1;
    void *temp_v1_2;
    void *var_a0;
    void *var_a0_2;
    void *var_s0;
    void *var_s0_2;

    var_s0 = &D_800AF630 + 0x65A8;
    temp_v1 = &D_800AF630 + 0x6688;
    if ((u32) var_s0 < (u32) temp_v1) {
        var_a0 = var_s0;
        do {
            func_80016714((u32) var_a0, 0x38);
            var_s0 += 0x38;
            var_a0 = var_s0;
        } while ((u32) var_s0 < (u32) temp_v1);
    }
    var_s0_2 = &D_800AF630 + 0x2A8;
    temp_v1_2 = &D_800AF630 + 0x4B8;
    if ((u32) var_s0_2 < (u32) temp_v1_2) {
        var_a0_2 = var_s0_2;
        do {
            func_80016714((u32) var_a0_2, 0x84);
            var_s0_2 += 0x84;
            var_a0_2 = var_s0_2;
        } while ((u32) var_s0_2 < (u32) temp_v1_2);
    }
}
#endif
