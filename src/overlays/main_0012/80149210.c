/* Overlay range [80149210,80149228) from MAIN.CD member 0012.
 * SHA256(span)=971545ab5eafaf472a7b66c54b71ea6fd6a5880e9eb1c3573cab34719307ae9c.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00A21025)
MUSASHI_NATIVE_MIPS_WORD(0xAC8201E4)
MUSASHI_NATIVE_MIPS_WORD(0xA48501E4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA48501E6)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80149210 - 6 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80149210(s32 a0, s32 a1) {
    *(s32 *)((s32)a0 + 0x1E4) = a1 | (a1 << 16);
    *(s16 *)((s32)a0 + 0x1E4) = a1;
    *(s16 *)((s32)a0 + 0x1E6) = a1;
}
#endif
