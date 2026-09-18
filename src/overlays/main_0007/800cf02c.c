/* Overlay range [800CF02C,800CF068) from MAIN.CD member 0007.
 * SHA256(span)=91d18c77e2ebae9dee8f3c1bff7a406366ed313b4ea08acc0ce823bcdc58df63.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x944299E4)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800D)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22133C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_800CF02C - 15 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u16 D_800B99E4;
extern u8 D_800CFABF;
extern u8 D_800CFAC4[];
extern u8 D_800CFAD4[];
extern void (*D_800CFADC[])(void);
extern s32 D_800D1364;
extern u8 D_800AF630[];
extern void func_8001534C(int, void *, int, int, int, int);
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_800183E0(void *a0);
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);
extern s8 D_800B9A11;
extern u16 D_800B99E8;
extern s32 D_800D130C;
extern s32 func_800167F0(s32 a0);
extern u16 D_800B99E6;
extern void (*D_800D133C[])(void);
extern void func_8001AA98(void *a0);
extern s32 D_800D1368;
extern s32 D_800D1370;
extern s32 D_800D1374;
extern void (*D_800D1344[])(void);
extern void func_800CF408(s32 a0, s32 a1);
extern void func_800CF6D0(s32 a0, u32 a1);
extern s32 D_800D136C;
extern s32 func_800CF3B0();
extern s32 func_800149E0(s32);
extern u8 *D_800A5E60;
extern u32 wD_800AA60C[] __asm__("D_800AA60C");
extern s16 D_800B9A02;
extern u8 D_800AA60C[];

void func_800CF02C(void) {
    D_800D133C[D_800B99E4]();
}
#endif
