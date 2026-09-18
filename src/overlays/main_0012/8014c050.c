/* Overlay range [8014C050,8014C088) from MAIN.CD member 0012.
 * SHA256(span)=f3180e970685ce696574c458e434e126009d7a83daa52e4629f1d2e604da38d5.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x2463D030)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10450006)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2C82001E)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x24630058)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014C050 - 14 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 D_8011D030;

s32 func_8014C050(s32 a0, s32 a1) {
    u32 i = 0;
    s32 p = (s32)&D_8011D030;
    for (; i < 0x1E; i++) {
        if (*(u16 *)p == a1) {
            return p;
        }
        p += 0x58;
    }
    return 0;
}
#endif
