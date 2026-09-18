/* Overlay range [801518D8,80151924) from MAIN.CD member 0012.
 * SHA256(span)=77393231992d0f9820e76ebc707139d83f4090f54db5349d5d5041394acec2c8.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9083003E)
MUSASHI_NATIVE_MIPS_WORD(0x2402001B)
MUSASHI_NATIVE_MIPS_WORD(0x1062000B)
MUSASHI_NATIVE_MIPS_WORD(0x2402001C)
MUSASHI_NATIVE_MIPS_WORD(0x10620009)
MUSASHI_NATIVE_MIPS_WORD(0x2402000F)
MUSASHI_NATIVE_MIPS_WORD(0x10620007)
MUSASHI_NATIVE_MIPS_WORD(0x24020010)
MUSASHI_NATIVE_MIPS_WORD(0x10620005)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0x10620003)
MUSASHI_NATIVE_MIPS_WORD(0x24020013)
MUSASHI_NATIVE_MIPS_WORD(0x14620003)
MUSASHI_NATIVE_MIPS_WORD(0x38620017)
MUSASHI_NATIVE_MIPS_WORD(0x08054647)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801518D8 - 19 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_801518D8(s32 a0) {
    u8 v1 = *(u8*)(a0 + 0x3E);
    if (v1 == 0x1B) return 1;
    if (v1 == 0x1C) return 1;
    if (v1 == 0xF) return 1;
    if (v1 == 0x10) return 1;
    if (v1 == 0x3) return 1;
    if (v1 != 0x13) return v1 == 0x17;
    return 1;
}
#endif
