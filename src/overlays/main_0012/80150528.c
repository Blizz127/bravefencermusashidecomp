/* Overlay range [80150528,801505FC) from MAIN.CD member 0012.
 * SHA256(span)=ffcbf60abcad76d2e4ebb27f87f29a0b19b4b9f423f59193f08b58c72cee67a3.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB40020)
MUSASHI_NATIVE_MIPS_WORD(0x0080A021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0x00A09021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB3001C)
MUSASHI_NATIVE_MIPS_WORD(0x00C09821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x3C118012)
MUSASHI_NATIVE_MIPS_WORD(0x263102A0)
MUSASHI_NATIVE_MIPS_WORD(0x26236480)
MUSASHI_NATIVE_MIPS_WORD(0x0223102B)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0028)
MUSASHI_NATIVE_MIPS_WORD(0xAFB50024)
MUSASHI_NATIVE_MIPS_WORD(0x1040001B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0060A821)
MUSASHI_NATIVE_MIPS_WORD(0x26300020)
MUSASHI_NATIVE_MIPS_WORD(0x96220000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x9602003C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420080)
MUSASHI_NATIVE_MIPS_WORD(0x1040000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8E050038)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10A00008)
MUSASHI_NATIVE_MIPS_WORD(0x02403021)
MUSASHI_NATIVE_MIPS_WORD(0x8E040000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04D693)
MUSASHI_NATIVE_MIPS_WORD(0x02603821)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x08054175)
MUSASHI_NATIVE_MIPS_WORD(0xAE9101A4)
MUSASHI_NATIVE_MIPS_WORD(0x2631010C)
MUSASHI_NATIVE_MIPS_WORD(0x0235102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE9)
MUSASHI_NATIVE_MIPS_WORD(0x2610010C)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x8FB50024)
MUSASHI_NATIVE_MIPS_WORD(0x8FB40020)
MUSASHI_NATIVE_MIPS_WORD(0x8FB3001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0030)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80150528 - 53 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u8 D_801202A0[];
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);

s32 func_80150528(void *arg0, void *arg1, void *arg2)
{
    u8 *p = D_801202A0;
    /* Inline limit expression (NOT a cached `end` local): gcc hoists the
     * loop-invariant `D_801202A0 + 0x6480` into the preheader, landing it in a
     * callee-saved reg via a temp->saved copy (addu $s5,$v1,$zero) because it
     * is live across the jal. A cached `end` local instead keeps the limit in
     * one saved reg (52 ins, wrong regalloc). */
    if (p < D_801202A0 + 0x6480) {
        do {
            if (*(u16*)p != 0) {
                if ((*(u16*)(p + 0x5C) & 0x80) != 0) {
                    if (*(s32*)(p + 0x58) != 0) {
                        if (((s32 (*)(s32, s32, s32, s32))func_80135A4C)(
                                *(s32*)(p + 0x20), *(s32*)(p + 0x58),
                                (s32)arg1, (s32)arg2) != 0) {
                            *(s32*)((u8*)arg0 + 0x1A4) = (s32)p;
                            return 1;
                        }
                    }
                }
            }
            p += 0x10C;
        } while (p < D_801202A0 + 0x6480);
    }
    return 0;
}
#endif
