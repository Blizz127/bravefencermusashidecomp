/* Overlay range [8012BF10,8012BF4C) from MAIN.CD member 0012.
 * SHA256(span)=af1a7f322858054394ee8ff5c6fcb0b7001c7cc42f88c03fee372fcf47fd5c28.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C82001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0804AFCC)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0804AFD1)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0xAC85001C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012BF10 - 15 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_8012BF10(s32 a0, s32 a1) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 == 0) {
        v0 = 1;
    } else {
        v0 -= 1;
        *(s32*)(a0 + 0x1C) = v0;
        v0 = (u32)v0 < 1;
    }
    if (v0 != 0) {
        *(s32*)(a0 + 0x1C) = a1;
        return 1;
    }
    return 0;
}
#endif
