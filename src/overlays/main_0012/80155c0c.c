/* Overlay range [80155C0C,80155C64) from MAIN.CD member 0012.
 * SHA256(span)=7d545f436d3195157ba0385303bdfb3a1bd6b381eced1b835a05007767904232.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFA8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00050)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0054)
MUSASHI_NATIVE_MIPS_WORD(0x8E020044)
MUSASHI_NATIVE_MIPS_WORD(0x960300B8)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0xAE020044)
MUSASHI_NATIVE_MIPS_WORD(0x34028000)
MUSASHI_NATIVE_MIPS_WORD(0x14620007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800D)
MUSASHI_NATIVE_MIPS_WORD(0x24A54DD4)
MUSASHI_NATIVE_MIPS_WORD(0x0C05509D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0054)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00050)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0058)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80155C0C - 22 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern u8 D_800D4DD4[];

void func_80155C0C(s32 *a0) {
    u8 sp10[0x40];
    (void)sp10;
    a0[0x44 / 4] |= 2;
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_80154274(a0, (s32)D_800D4DD4);
        func_80146CA0(a0);
    }
}
#endif
