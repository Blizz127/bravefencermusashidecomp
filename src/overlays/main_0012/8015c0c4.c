/* Overlay range [8015C0C4,8015C128) from MAIN.CD member 0012.
 * SHA256(span)=a3bb2981808fae7b59ef0cb8f1eb824a9008982fd141aa3e2306d6bd26b976a7.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x3C030008)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x844252B0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAE030238)
MUSASHI_NATIVE_MIPS_WORD(0x00021180)
MUSASHI_NATIVE_MIPS_WORD(0xAE020234)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x844252B4)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x00021180)
MUSASHI_NATIVE_MIPS_WORD(0x0C055054)
MUSASHI_NATIVE_MIPS_WORD(0xAE02023C)
MUSASHI_NATIVE_MIPS_WORD(0x0C0554EA)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B28)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8015C0C4 - 25 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80154150(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_8015C0C4(s32 a0) {
    s32 t = D_801152B0 << 6;
    *(s32 *)(a0 + 0x238) = 0x80000;
    *(s32 *)(a0 + 0x234) = t;
    *(s32 *)(a0 + 0x23C) = D_801152B4 << 6;
    func_80154150(a0, 0x11);
    func_801553A8((s32 *)a0);
    func_80146CA0((void *)a0);
}
#endif
