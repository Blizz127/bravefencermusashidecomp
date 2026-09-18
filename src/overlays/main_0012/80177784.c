/* Overlay range [80177784,801777BC) from MAIN.CD member 0012.
 * SHA256(span)=e28f1647fdc59471d42580082d2df201360bf33b7b3a6fdedce5ac1c9e0a6cb5.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C077480)
MUSASHI_NATIVE_MIPS_WORD(0x34E78080)
MUSASHI_NATIVE_MIPS_WORD(0x2482FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030300)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0x24820014)
MUSASHI_NATIVE_MIPS_WORD(0xAC870004)
MUSASHI_NATIVE_MIPS_WORD(0xAC850008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC86000C)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80177784 - 14 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3) {
    *(u32 *)((s32)a0 + 0x0) = (((s32)a0 - 0x14) & 0xFFFFFF) | 0x3000000;
    *(u32 *)((s32)a0 + 0x4) = 0x74808080;
    *(s32 *)((s32)a0 + 0x8) = a1;
    *(s32 *)((s32)a0 + 0xC) = a2;
    return (void *)((s32)a0 + 0x14);
}
#endif
