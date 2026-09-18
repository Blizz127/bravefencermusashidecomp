/* Overlay range [80153B58,80153BD8) from MAIN.CD member 0012.
 * SHA256(span)=82714c7896e6dc43f6104ae65d339383104dbbe820aefeae5d08adb20f755a4a.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x944299DA)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80153B58 - 32 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern u16 D_800B99DA;
extern s32 func_8016DA04(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_80153B58(s32 *a0) {
    if ((D_800B99DA & 0x3) == 0) {
        func_8016DA04((s32)a0);
    }
    if ((D_800B99DA & 0x1) == 0) {
        func_80146A6C(3, a0,
                      *(s16 *)((u8 *)a0 + 6),
                      *(s16 *)((u8 *)a0 + 0xA),
                      *(s16 *)((u8 *)a0 + 0xE),
                      0x8880000, 0x18009000);
    }
}
#endif
