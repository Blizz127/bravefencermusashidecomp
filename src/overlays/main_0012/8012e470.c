/* Overlay range [8012E470,8012E4C8) from MAIN.CD member 0012.
 * SHA256(span)=376e20a61843a59643a97940655e41504ad94b5a314904a5d821ea1368ee7b99.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C850020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84A30018)
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420003)
MUSASHI_NATIVE_MIPS_WORD(0x00021083)
MUSASHI_NATIVE_MIPS_WORD(0x00621021)
MUSASHI_NATIVE_MIPS_WORD(0xA4A2001C)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20018)
MUSASHI_NATIVE_MIPS_WORD(0x8C82001C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0804B930)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xAC82001C)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8012E470 - 22 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


s32 func_8012E470(s32 a0) {
    s32 a1 = *(s32*)(a0 + 0x20);
    s32 v1 = *(s16*)(a1 + 0x18);
    s32 v0 = v1 + (0x1000 - v1) / 4;
    *(s16*)(a1 + 0x18) = (*(s16*)(a1 + 0x1C) = v0);
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 != 0) {
        v0 -= 1;
        *(s32*)(a0 + 0x1C) = v0;
        v1 = v0;
        return (u32)v1 < 1;
    }
    return 1;
}
#endif
