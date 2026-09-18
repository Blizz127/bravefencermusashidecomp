/* Overlay range [8016FD08,8016FD7C) from MAIN.CD member 0012.
 * SHA256(span)=c87451266b7139822463fe5129d859ba065ad57ea55c3751a9ff81c928b7dd38.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C996)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x10400012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B64)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x960200AC)
MUSASHI_NATIVE_MIPS_WORD(0x960300AA)
MUSASHI_NATIVE_MIPS_WORD(0x34420040)
MUSASHI_NATIVE_MIPS_WORD(0x34630040)
MUSASHI_NATIVE_MIPS_WORD(0xA60300AA)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x2463F738)
MUSASHI_NATIVE_MIPS_WORD(0xA60200AC)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0xAC620000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C664)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016FD08 - 29 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80172658(s32 *a0);
extern void func_80146D90(s32 a0);
extern s32 func_80171990(u8 *a0);
extern void *D_8011F738;

void func_8016FD08(u8 *s0) {
    s32 *p;
    if (func_80172658((s32 *)s0)) {
        func_80146D90((s32)s0);
        *(u16 *)(s0 + 0xAC) = *(u16 *)(s0 + 0xAC) | 0x40;
        *(u16 *)(s0 + 0xAA) = *(u16 *)(s0 + 0xAA) | 0x40;
        p = (s32 *)&D_8011F738;
        if ((*p = *p - 1) == 0) {
            func_80171990(s0);
        }
    }
}
#endif
