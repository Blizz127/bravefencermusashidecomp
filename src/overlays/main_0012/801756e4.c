/* Overlay range [801756E4,80175798) from MAIN.CD member 0012.
 * SHA256(span)=7a09d7cc43495a17e74c67f48e361cea1b7e57a77c34e271b015421db878022b.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x92240005)
MUSASHI_NATIVE_MIPS_WORD(0x92220006)
MUSASHI_NATIVE_MIPS_WORD(0x3C10800C)
MUSASHI_NATIVE_MIPS_WORD(0x26109A02)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x304300FF)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0xA2220006)
MUSASHI_NATIVE_MIPS_WORD(0x92220006)
MUSASHI_NATIVE_MIPS_WORD(0x248400FF)
MUSASHI_NATIVE_MIPS_WORD(0xA2240005)
MUSASHI_NATIVE_MIPS_WORD(0xA6230010)
MUSASHI_NATIVE_MIPS_WORD(0xA623000C)
MUSASHI_NATIVE_MIPS_WORD(0xA6220016)
MUSASHI_NATIVE_MIPS_WORD(0xA6220012)
MUSASHI_NATIVE_MIPS_WORD(0xA622000E)
MUSASHI_NATIVE_MIPS_WORD(0xA6220014)
MUSASHI_NATIVE_MIPS_WORD(0x86040000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D76A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x86040000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D6AE)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x86040000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D851)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x92220005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x92220001)
MUSASHI_NATIVE_MIPS_WORD(0xA2200008)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0xA2220001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801756E4 - 45 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80175DA8(s32 a0);
extern void func_80175AB8(s32 a0);
extern void func_80176144(s32 a0);
extern short D_800B9A02;

void func_801756E4(s32 arg0) {
    register s32 a __asm__("$17") = arg0;
    register short *p __asm__("$16");
    s32 f5;
    s32 sum;
    s16 neg;
    s32 b6;
    p = &D_800B9A02;
    f5 = *(u8 *)(a + 5);
    sum = *(u8 *)(a + 6) + f5;
    neg = -(s16)(sum & 0xFF);
    *(u8 *)(a + 6) = sum;
    __asm__ __volatile__("" : : : "memory");
    b6 = *(u8 *)(a + 6);
    *(u8 *)(a + 5) = (u8)f5 + 0xFF;
    *(s16 *)(a + 0x10) = neg;
    *(s16 *)(a + 0xc) = neg;
    *(u16 *)(a + 0x16) = b6;
    *(u16 *)(a + 0x12) = b6;
    *(u16 *)(a + 0xe) = b6;
    *(u16 *)(a + 0x14) = b6;
    func_80175DA8(*p);
    func_80175AB8(*p);
    func_80176144(*p);
    if (*(u8 *)(a + 5) == 0) {
        *(u8 *)(a + 8) = 0;
        *(u8 *)(a + 1) = *(u8 *)(a + 1) + 1;
    }
}
#endif
