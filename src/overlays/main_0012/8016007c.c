/* Overlay range [8016007C,801600D0) from MAIN.CD member 0012.
 * SHA256(span)=b405897257a35b73974177f076b9cf7876e369e43e17cdadf7c03a6f647ef1de.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x2403FFEF)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x8C820044)
MUSASHI_NATIVE_MIPS_WORD(0xAC800184)
MUSASHI_NATIVE_MIPS_WORD(0xA480018A)
MUSASHI_NATIVE_MIPS_WORD(0xA4800188)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0xAC820044)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0229A17)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA42270C0)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016007C - 21 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_80154A74(s32 a0, s32 a1);
extern u8 D_800B9A17;
extern u16 D_801270C0;

void func_8016007C(s32 a0) {
    *(s32 *)(a0 + 0x184) = 0;
    *(s16 *)(a0 + 0x18A) = 0;
    *(s16 *)(a0 + 0x188) = 0;
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & ~0x10;
    D_800B9A17 = 1;
    func_80154A74(a0, 0x11);
    D_801270C0 = 1;
}
#endif
