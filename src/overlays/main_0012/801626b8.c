/* Overlay range [801626B8,80162714) from MAIN.CD member 0012.
 * SHA256(span)=09dafa4dffe1f0ebba35cd3ec4dcaf5052ccd290b3c0dea02ae4e38881c5b0e4.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A477)
MUSASHI_NATIVE_MIPS_WORD(0x24040012)
MUSASHI_NATIVE_MIPS_WORD(0x30427FFF)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x0C03438C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x93A30011)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00031040)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x93A30010)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801626B8 - 23 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);

int func_801626B8(void) {
    short local;
    int lo;
    local = func_800291DC(0x12) & 0x7FFF;
    local = func_800D0E30(&local);
    lo = *(unsigned char *)&local;
    return (short)(*((unsigned char *)&local + 1) * 100 + lo);
}
#endif
