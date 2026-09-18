/* Overlay range [801719A4,80171A04) from MAIN.CD member 0012.
 * SHA256(span)=1e4261792af44e9d627aa8a2e58189312129372bb0bc8f28d2da50eee4326344.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000F)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0x8C8301FC)
MUSASHI_NATIVE_MIPS_WORD(0x00461021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x8C420000)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0x00270821)
MUSASHI_NATIVE_MIPS_WORD(0xAC22F738)
MUSASHI_NATIVE_MIPS_WORD(0x00C5102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x24E70004)
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00461021)
MUSASHI_NATIVE_MIPS_WORD(0xA0820214)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801719A4 - 24 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void *D_8011F738;

void func_801719A4(int a0, int a1)
{
    u32 i;
    s32 off;
    s32 pad[1];
    for (i = 0; i < a1; i++) {
        off = i * 4;
        *(s32*)((s32)&D_8011F738 + off) =
            *(s32*)(((*(u8*)(a0 + 0x214) + i) << 2) + *(s32*)(a0 + 0x1FC));
    }
    *(u8*)(a0 + 0x214) += i;
}
#endif
