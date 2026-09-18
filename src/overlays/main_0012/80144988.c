/* Overlay range [80144988,801449C8) from MAIN.CD member 0012.
 * SHA256(span)=93da214a50bb0330447a0607429b679cc2d56560db2b691b17baa476015ca763.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x8C830064)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFC0)
MUSASHI_NATIVE_MIPS_WORD(0xA482000A)
MUSASHI_NATIVE_MIPS_WORD(0x8C620010)
MUSASHI_NATIVE_MIPS_WORD(0x8C830064)
MUSASHI_NATIVE_MIPS_WORD(0xAC820010)
MUSASHI_NATIVE_MIPS_WORD(0x8C620014)
MUSASHI_NATIVE_MIPS_WORD(0x8C830064)
MUSASHI_NATIVE_MIPS_WORD(0xAC820014)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x8C630018)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA4820002)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC830018)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80144988 - 16 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80144988(s32 a0) {
    s32 t;
    *(u16*)(a0 + 0xA) = *(u16*)(a0 + 0xA) - 0x40;
    *(s32*)(a0 + 0x10) = *(s32*)(*(s32*)(a0 + 0x64) + 0x10);
    *(s32*)(a0 + 0x14) = *(s32*)(*(s32*)(a0 + 0x64) + 0x14);
    t = *(s32*)(*(s32*)(a0 + 0x64) + 0x18);
    *(u16*)(a0 + 0x2) = *(u16*)(a0 + 0x2) + 1;
    *(s32*)(a0 + 0x18) = t;
}
#endif
