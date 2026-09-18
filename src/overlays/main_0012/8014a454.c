/* Overlay range [8014A454,8014A4B4) from MAIN.CD member 0012.
 * SHA256(span)=19a35159056383a59b3ba346195d5428eb2c648001423ec9486505d767b1c6ba.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x9482003C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30424000)
MUSASHI_NATIVE_MIPS_WORD(0x1040000E)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8C820020)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94450012)
MUSASHI_NATIVE_MIPS_WORD(0x84840042)
MUSASHI_NATIVE_MIPS_WORD(0x24A50800)
MUSASHI_NATIVE_MIPS_WORD(0x0C004A98)
MUSASHI_NATIVE_MIPS_WORD(0x30A50FFF)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x284202AA)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8014A454 - 24 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 func_80012A60(s32 a0, s32 a1);

s32 func_8014A454(s32 a0) {
    s32 v0;
    if (*(u16 *)(a0 + 0x3C) & 0x4000) {
        v0 = (s16)func_80012A60(*(s16 *)(a0 + 0x42),
                                (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800) & 0xFFF);
        if (v0 < 0x2AA) {
            return 1;
        }
    }
    return 0;
}
#endif
