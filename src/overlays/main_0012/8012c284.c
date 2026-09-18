/* Overlay range [8012C284,8012C2D0) from MAIN.CD member 0012.
 * SHA256(span)=52a25608f3f8af9aa0d53700f62225c99f6bfba1119ed66e45543cb276f8a828.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24636720)
MUSASHI_NATIVE_MIPS_WORD(0x14800005)
MUSASHI_NATIVE_MIPS_WORD(0x2484010C)
MUSASHI_NATIVE_MIPS_WORD(0x0804B0A9)
MUSASHI_NATIVE_MIPS_WORD(0x24649B80)
MUSASHI_NATIVE_MIPS_WORD(0x0804B0B2)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x10830008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x94820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2484010C)
MUSASHI_NATIVE_MIPS_WORD(0x1483FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012C284 - 19 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_80126720[];

u16 *func_8012C284(u16 *a0)
{
    u16 *end;
    end = (u16 *)D_80126720;
    if (a0 == 0) {
        a0 = (u16 *)(D_80126720 - 0x6480);
    } else {
        a0 = (u16 *)((u8 *)a0 + 0x10C);
    }
    while (a0 != end) {
        if (*a0 == 0) {
            return a0;
        }
        a0 = (u16 *)((u8 *)a0 + 0x10C);
    }
    return 0;
}
#endif
