/* Main-exec range [80041354,800413B8) from the SLUS executable.
 * SHA256(span)=80b44d0e8d4b4e8a8d7f647596ee37309a9267021f2df081a8d1a7db9b20e36a.
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
MUSASHI_NATIVE_MIPS_WORD(0x3C07800C)
MUSASHI_NATIVE_MIPS_WORD(0x24E79B36)
MUSASHI_NATIVE_MIPS_WORD(0xA4E40000)
MUSASHI_NATIVE_MIPS_WORD(0x3084FF00)
MUSASHI_NATIVE_MIPS_WORD(0x00042203)
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021100)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x94620058)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A20000)
MUSASHI_NATIVE_MIPS_WORD(0x9462005A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4C20000)
MUSASHI_NATIVE_MIPS_WORD(0x84E20000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80041354 - 25 words. Promoted from vendor/bfm-decomp
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

s32 func_80041354(s32 param_1, u16 *param_2, u16 *param_3)
{
    s32 base;
    s16 *attr;
    s32 vab;

    base = D_800C73D8[param_1 & 0xFF];
    attr = &D_800B9B36;
    *attr = param_1;
    vab = (param_1 & 0xFF00) >> 8;
    base += vab * 0xB0;
    *param_2 = *(u16 *)(base + 0x58);
    *param_3 = *(u16 *)(base + 0x5A);
    return *attr;
}
#endif
