/* Overlay range [801612B8,8016130C) from MAIN.CD member 0012.
 * SHA256(span)=7ba46055884c2bcca8d1a5e12724bddaca8530085ccf59dda897a015fd5ae973.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0x30A50001)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x14A00003)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C053A4D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05330A)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x0C053CFA)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x02021025)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801612B8 - 21 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);

s32 func_801612B8(void * a0, s32 a1)
{
    register s32 p __asm__("$17");
    register s32 v0 __asm__("$16");
    s32 v1;
    p = a0;
    if ((a1 & 1) == 0) {
        func_8014E934(p);
    }
    v0 = ((s32 (*)(s32))func_8014CC28)(p);
    __asm__ __volatile__("" : : "r"(v0));
    v1 = ((s32 (*)(s32))func_8014F3E8)(p);
    return v0 | v1;
}
#endif
