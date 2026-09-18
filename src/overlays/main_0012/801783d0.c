/* Overlay range [801783D0,80178438) from MAIN.CD member 0012.
 * SHA256(span)=1c7a8836a1d1776db62d639b25a70f67604568b7602f4c6690850324fd8b6bbd.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x28C2000A)
MUSASHI_NATIVE_MIPS_WORD(0x14400012)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x3C096666)
MUSASHI_NATIVE_MIPS_WORD(0x35296667)
MUSASHI_NATIVE_MIPS_WORD(0x00890018)
MUSASHI_NATIVE_MIPS_WORD(0x000417C3)
MUSASHI_NATIVE_MIPS_WORD(0x00005010)
MUSASHI_NATIVE_MIPS_WORD(0x000A1883)
MUSASHI_NATIVE_MIPS_WORD(0x00622023)
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x000418C0)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00C21023)
MUSASHI_NATIVE_MIPS_WORD(0x00E21004)
MUSASHI_NATIVE_MIPS_WORD(0x01024025)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x28C2000A)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x24E70004)
MUSASHI_NATIVE_MIPS_WORD(0x00E61004)
MUSASHI_NATIVE_MIPS_WORD(0x01024025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A81004)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801783D0 - 26 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


u32 func_801783D0(s32 a0, s32 a1) {
    s32 t0;
    s32 a2;
    s32 a3;
    t0 = 0;
    a2 = a0;
    a3 = 0;
    while (a2 >= 10) {
        a0 = a0 / 10;
        t0 = t0 | ((a2 - (a0 * 2 + a0 * 8)) << a3);
        a2 = a0;
        a3 += 4;
    }
    t0 = t0 | (a2 << a3);
    return t0 << a1;
}
#endif
