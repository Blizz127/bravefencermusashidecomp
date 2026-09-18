/* Overlay range [801628F4,80162968) from MAIN.CD member 0012.
 * SHA256(span)=40639445fe72781923afa85337553da894fa3c270fc17be929216ea6cb2abd3c.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C860004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84C2007E)
MUSASHI_NATIVE_MIPS_WORD(0x8C850008)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x3C038000)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x08058A4C)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x3C037FFF)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20004)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0xACA20004)
MUSASHI_NATIVE_MIPS_WORD(0x84C20078)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820020)
MUSASHI_NATIVE_MIPS_WORD(0x84C2007A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAC820024)
MUSASHI_NATIVE_MIPS_WORD(0x84C2007C)
MUSASHI_NATIVE_MIPS_WORD(0x0C058A5A)
MUSASHI_NATIVE_MIPS_WORD(0xAC820028)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801628F4 - 29 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80162968(s32 a0);

void func_801628F4(s32 *a0) {
    s16 *a2 = (s16 *)a0[0x4 / 4];
    s32 *a1 = (s32 *)a0[0x8 / 4];
    if (*(s16 *)((u8 *)a2 + 0x7E) != 0) {
        a1[0x4 / 4] |= 0x80000000;
    } else {
        a1[0x4 / 4] &= 0x7FFFFFFF;
    }
    a0[0x20 / 4] = *(s16 *)((u8 *)a2 + 0x78);
    a0[0x24 / 4] = *(s16 *)((u8 *)a2 + 0x7A);
    a0[0x28 / 4] = *(s16 *)((u8 *)a2 + 0x7C);
    func_80162968((s32)a0);
}
#endif
