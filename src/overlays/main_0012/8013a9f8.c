/* Overlay range [8013A9F8,8013AA24) from MAIN.CD member 0012.
 * SHA256(span)=f0579ddda68d5a018cb893d350abcdc60236852c2d441a4887000fa0e7bc77ba.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
MUSASHI_NATIVE_MIPS_WORD(0x24A5FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x30A5FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2CA50005)
MUSASHI_NATIVE_MIPS_WORD(0x10A00004)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x00021280)
MUSASHI_NATIVE_MIPS_WORD(0xA482000E)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8013A9F8 - 11 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_8013A9F8(s32 a0, s32 a1) {
    s32 orig = a1;
    a1 -= 2;
    a1 &= 0xFFFF;
    if ((u32)a1 < 5) {
        s32 b = orig & 0xFFFF;
        b -= 2;
        b <<= 10;
        *(s16*)(a0 + 0xE) = b;
    }
}
#endif
