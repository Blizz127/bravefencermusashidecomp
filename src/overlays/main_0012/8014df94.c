/* Overlay range [8014DF94,8014E048) from MAIN.CD member 0012.
 * SHA256(span)=c9806e7bbcf4d5fc248d6b1b17d9ae1a2b8c5bf7302eedb1f832f9d3bd8d10da.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x94C40088)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A40010)
MUSASHI_NATIVE_MIPS_WORD(0x94C2008A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x94C5008C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A50014)
MUSASHI_NATIVE_MIPS_WORD(0x94C30006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30018)
MUSASHI_NATIVE_MIPS_WORD(0x94C2000A)
MUSASHI_NATIVE_MIPS_WORD(0x00641823)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001A)
MUSASHI_NATIVE_MIPS_WORD(0x94C2000E)
MUSASHI_NATIVE_MIPS_WORD(0x00832023)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A40018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001C)
MUSASHI_NATIVE_MIPS_WORD(0x00451023)
MUSASHI_NATIVE_MIPS_WORD(0x00A22823)
MUSASHI_NATIVE_MIPS_WORD(0xA7A2001C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A5001C)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20170)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0x00C02021)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0538A1)
MUSASHI_NATIVE_MIPS_WORD(0x27A60018)
MUSASHI_NATIVE_MIPS_WORD(0x0805380E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x0C053812)
MUSASHI_NATIVE_MIPS_WORD(0x27A60018)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014DF94 - 45 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2);

void func_8014DF94(s32 arg0) {
    s16 a[3];
    s16 b[3];
    register s32 u88 __asm__("$4");
    register s32 u8C __asm__("$5");
    s32 t;
    s32 t2;
    u88 = *(u16 *)(arg0 + 0x88);
    a[0] = u88;
    a[1] = *(u16 *)(arg0 + 0x8A) - 0x10;
    u8C = *(u16 *)(arg0 + 0x8C);
    a[2] = u8C;
    t = *(u16 *)(arg0 + 6);
    b[0] = t;
    b[1] = *(u16 *)(arg0 + 0xA) - 0x10;
    t = t - u88;
    t2 = *(u16 *)(arg0 + 0xE);
    u88 = u88 - t;
    b[0] = t;
    __asm__ __volatile__("" : : : "memory");
    b[0] = u88;
    b[2] = t2;
    __asm__ __volatile__("" : : : "memory");
    t2 = t2 - u8C;
    u8C = u8C - t2;
    b[2] = t2;
    __asm__ __volatile__("" : : : "memory");
    b[2] = u8C;
    if (*(s32 *)(arg0 + 0x170) == 0) {
        func_8014E284(arg0, a, b);
    } else {
        func_8014E048(arg0, a, b);
    }
}
#endif
