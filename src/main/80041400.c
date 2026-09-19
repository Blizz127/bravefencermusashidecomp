/* Main-exec range [80041400,80041448) from the SLUS executable.
 * SHA256(span)=b414e7f891d997590d94459b3e1af123475cc7c2ff89064304b237df97a94f8b.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x308200FF)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C2373D8)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA4249B36)
MUSASHI_NATIVE_MIPS_WORD(0x3084FF00)
MUSASHI_NATIVE_MIPS_WORD(0x00042203)
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021100)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x8462005A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* func_80041400 - 18 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 D_800C73D8[];
extern s16 D_800B9B36;
extern u8 D_800AE614;
extern s16 D_80079590[];
extern u8 D_80079592[];
extern s16 D_80079596[][26];
extern s16 D_80079598[];
extern s16 D_8007959A[];
extern s16 D_8007959C[];
extern s16 D_8007959E[];
extern u8 *D_800A6578;
extern u8 *D_800A6580;
extern s32 D_800A6584;
extern s16 D_800A6434;
extern s16 D_800B9B58[];
extern u8 D_800A4620[];
extern u8   D_800AE614;
extern s16  D_80079596[][26];
extern u16  D_800B9B3A;
extern void func_80040868(s32);

s32 func_80041400(s32 param_1)
{
    s32 base;
    s32 vab;

    base = D_800C73D8[param_1 & 0xFF];
    __asm__ __volatile__("" ::: "memory");
    D_800B9B36 = param_1;
    vab = (param_1 & 0xFF00) >> 8;
    base += vab * 0xB0;
    return *(s16 *)(base + 0x5A);
}
#endif
