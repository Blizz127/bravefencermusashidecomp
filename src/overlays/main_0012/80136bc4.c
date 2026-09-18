/* Overlay range [80136BC4,80136C1C) from MAIN.CD member 0012.
 * SHA256(span)=480288f84195d8170e11a9a7aa663f5f5962f32e49df56cee7e6a54ecc30ea1a.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830008)
MUSASHI_NATIVE_MIPS_WORD(0x24020020)
MUSASHI_NATIVE_MIPS_WORD(0x14620011)
MUSASHI_NATIVE_MIPS_WORD(0x24830020)
MUSASHI_NATIVE_MIPS_WORD(0x8C82000C)
MUSASHI_NATIVE_MIPS_WORD(0xAC830008)
MUSASHI_NATIVE_MIPS_WORD(0x8C830014)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC82000C)
MUSASHI_NATIVE_MIPS_WORD(0x8C820010)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0xAC830014)
MUSASHI_NATIVE_MIPS_WORD(0x8C83001C)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820018)
MUSASHI_NATIVE_MIPS_WORD(0x00641821)
MUSASHI_NATIVE_MIPS_WORD(0xAC83001C)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0xAC820018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80136BC4 - 22 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80136BC4(s32 a0) {
    if (*(s32*)(a0 + 0x8) == 0x20) {
        *(s32*)(a0 + 0x8) = a0 + 0x20;
        *(s32*)(a0 + 0xC) += a0;
        *(s32*)(a0 + 0x10) += a0;
        *(s32*)(a0 + 0x14) += a0;
        *(s32*)(a0 + 0x18) += a0;
        *(s32*)(a0 + 0x1C) += a0;
    }
}
#endif
