/* Overlay range [8014C168,8014C1A0) from MAIN.CD member 0012.
 * SHA256(span)=a615915d45cbd5c945ebf1504dd8e9a8a15164794ccde48f6316ee4834150bf7.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x246302A0)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10450006)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2C820060)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x2463010C)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014C168 - 14 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_801202A0[];

s32 func_8014C168(s32 * param_1, s32 param_2)
{
    u32 i;
    u16 *p;
    i = 0;
    p = (u16 *)D_801202A0;
    for (; i < 0x60; i++) {
        if (*p == param_2) {
            return p;
        }
        p = (u16 *)((u8 *)p + 0x10C);
    }
    return (u16 *)0;
}
#endif
