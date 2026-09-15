/* Overlay range [80148824,801488A8) from MAIN.CD member 0012.
 * SHA256(span)=0191bf98db38650cf3a148bccf2d1274051a2fb2d62398ea07cf56d43646b58a.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x948200AE)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021A02)
MUSASHI_NATIVE_MIPS_WORD(0x2463FF80)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x304200FF)
MUSASHI_NATIVE_MIPS_WORD(0x2442FF80)
MUSASHI_NATIVE_MIPS_WORD(0x14600005)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x04410011)
MUSASHI_NATIVE_MIPS_WORD(0x308200FF)
MUSASHI_NATIVE_MIPS_WORD(0x08052225)
MUSASHI_NATIVE_MIPS_WORD(0x00041023)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x00630018)
MUSASHI_NATIVE_MIPS_WORD(0x0461000B)
MUSASHI_NATIVE_MIPS_WORD(0x30A200FF)
MUSASHI_NATIVE_MIPS_WORD(0x08052225)
MUSASHI_NATIVE_MIPS_WORD(0x00051023)
MUSASHI_NATIVE_MIPS_WORD(0x00001812)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00420018)
MUSASHI_NATIVE_MIPS_WORD(0x00002812)
MUSASHI_NATIVE_MIPS_WORD(0x0C011F4F)
MUSASHI_NATIVE_MIPS_WORD(0x00652021)
MUSASHI_NATIVE_MIPS_WORD(0x304200FF)
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

s32 func_80047D3C(s32, s32);                        /* extern */

s32 func_80148824(void *arg0) {
    s32 temp_lo;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0xAE);
    temp_v1 = (temp_v0 >> 8) - 0x80;
    temp_v0_2 = (temp_v0 & 0xFF) - 0x80;
    if (temp_v1 == 0) {
        var_v0 = temp_v0_2 & 0xFF;
        if (temp_v0_2 < 0) {
            var_v0_2 = -temp_v0_2;
            goto block_7;
        }
    } else if (temp_v0_2 == 0) {
        var_v0 = temp_v1 & 0xFF;
        if (temp_v1 < 0) {
            var_v0_2 = -temp_v1;
            goto block_7;
        }
    } else {
        temp_lo = temp_v0_2 * temp_v0_2;
        var_v0_2 = func_80047D3C((temp_v1 * temp_v1) + temp_lo, temp_lo);
block_7:
        var_v0 = var_v0_2 & 0xFF;
    }
    return var_v0;
}
#endif
