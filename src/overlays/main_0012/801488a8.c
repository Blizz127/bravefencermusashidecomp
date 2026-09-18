/* Overlay range [801488A8,8014891C) from MAIN.CD member 0012.
 * SHA256(span)=f1d643f29936a018ecea6acbf834702bb644fd3db10e6415460d452cfcaf0a2d.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908300A9)
MUSASHI_NATIVE_MIPS_WORD(0x24020053)
MUSASHI_NATIVE_MIPS_WORD(0x1062000F)
MUSASHI_NATIVE_MIPS_WORD(0x28620054)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x24020041)
MUSASHI_NATIVE_MIPS_WORD(0x10620008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08052245)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x24020073)
MUSASHI_NATIVE_MIPS_WORD(0x10620006)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x08052245)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x948200AA)
MUSASHI_NATIVE_MIPS_WORD(0x08052245)
MUSASHI_NATIVE_MIPS_WORD(0x3042F000)
MUSASHI_NATIVE_MIPS_WORD(0x948400AE)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0x308300FF)
MUSASHI_NATIVE_MIPS_WORD(0x14620005)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00041202)
MUSASHI_NATIVE_MIPS_WORD(0x14430002)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801488A8 - 29 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_801488A8(u8 *a0) {
    u8 c;
    s32 v0;
    u32 h;
    s32 lo;
    c = a0[0xA9];
    switch (c) {
    case 0x41:
        v0 = *(u16 *)(a0 + 0xAA) & 0xF000;
        break;
    case 0x53:
    case 0x73:
        h = *(u16 *)(a0 + 0xAE);
        lo = h & 0xFF;
        if (lo != 0x80) {
            return 1;
        }
        if ((s32)(h >> 8) != lo) {
            return 1;
        }
        v0 = 0;
        break;
    default:
        v0 = 0;
        break;
    }
    return v0;
}
#endif
