/* Overlay range [8016E918,8016E95C) from MAIN.CD member 0012.
 * SHA256(span)=b7190236e10ad418865c4bf2542c3990948d61aa9fbd9d490d556934785be7a5.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00A03821)
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x28A5000A)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x00041400)
MUSASHI_NATIVE_MIPS_WORD(0x000212C3)
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x24635218)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x24C30001)
MUSASHI_NATIVE_MIPS_WORD(0xA0430000)
MUSASHI_NATIVE_MIPS_WORD(0xA0470003)
MUSASHI_NATIVE_MIPS_WORD(0xA0400001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8016E918 - 17 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern s32 D_80115218;

void func_8016E918(short param_1, short param_2) {
    char *p;
    if (param_2 < 10) {
        p = (char *)&D_80115218 + ((s32)param_1 << 5);
        p[0] = param_1 + 1;
        p[3] = param_2;
        p[1] = 0;
    }
}
#endif
