/* Overlay range [80160C28,80160CB4) from MAIN.CD member 0012.
 * SHA256(span)=f41b1d53f4890ffc068b5f8ddc22eedbc1bf095f1f0f14d7a9bb1a939fc56256.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C058482)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x14400018)
MUSASHI_NATIVE_MIPS_WORD(0x3C030001)
MUSASHI_NATIVE_MIPS_WORD(0x3463C000)
MUSASHI_NATIVE_MIPS_WORD(0x8E020238)
MUSASHI_NATIVE_MIPS_WORD(0x8E040020)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0xAE020238)
MUSASHI_NATIVE_MIPS_WORD(0x94820010)
MUSASHI_NATIVE_MIPS_WORD(0x9603023A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x30420FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4820010)
MUSASHI_NATIVE_MIPS_WORD(0x8E030020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x84620010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28420C00)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24020C00)
MUSASHI_NATIVE_MIPS_WORD(0xA4620010)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0xA48200B8)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80160C28 - 35 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80161208();
extern void func_80146CA0(void *a0);

void func_80160C28(void *arg0)
{
    s32 p;
    s32 q;
    register void *a __asm__("$4");
    if (func_80161208() == 0) {
        *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
        p = *(s32 *)((u8 *)arg0 + 0x20);
        *(u16 *)((u8 *)p + 0x10) =
            (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
        q = *(s32 *)((u8 *)arg0 + 0x20);
        if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
            a = arg0;
            __asm__ __volatile__("" : : "r"(a));
            *(u16 *)((u8 *)q + 0x10) = 0xc00;
            *(u16 *)((u8 *)a + 0xb8) = 1;
            func_80146CA0(a);
        }
    }
}
#endif
