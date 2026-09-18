/* Overlay range [8016197C,801619A4) from MAIN.CD member 0012.
 * SHA256(span)=e8ab3e29e739f4a995e7f0380f1426c3051402893ae374e0dabec40df253a493.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A20001)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x30A24000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0x000512C2)
MUSASHI_NATIVE_MIPS_WORD(0x30420004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016197C - 10 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_8016197C(s32 a0, s32 a1) {
    s32 v0;
    if (a1 & 1) {
        v0 = 1;
    } else if (a1 & 0x4000) {
        v0 = 2;
    } else {
        v0 = ((u32)a1 >> 11) & 4;
    }
    return v0;
}
#endif
