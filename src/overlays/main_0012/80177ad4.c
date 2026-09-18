/* Overlay range [80177AD4,80177B5C) from MAIN.CD member 0012.
 * SHA256(span)=756362ff1f6a6190e3c15e7130a711896255cad2787d8e9f5bb48c0197fe6d8e.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24080100)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x240B0003)
MUSASHI_NATIVE_MIPS_WORD(0x240A0001)
MUSASHI_NATIVE_MIPS_WORD(0x2409FEFF)
MUSASHI_NATIVE_MIPS_WORD(0x24860020)
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00021702)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104B0003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x144A0002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x24E20001)
MUSASHI_NATIVE_MIPS_WORD(0x00403821)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x28420004)
MUSASHI_NATIVE_MIPS_WORD(0xA0C30000)
MUSASHI_NATIVE_MIPS_WORD(0x00892024)
MUSASHI_NATIVE_MIPS_WORD(0x01042025)
MUSASHI_NATIVE_MIPS_WORD(0xA4C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE7)
MUSASHI_NATIVE_MIPS_WORD(0x24C60014)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80177AD4 - 34 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80177AD4(int param_1, unsigned int param_2) {
    register unsigned int c __asm__("$2");
    register unsigned int b __asm__("$3");
    char *base; short i; int f; int t;
    f = 0x100; i = 0; base = (char *)param_1;
    do {
        c = (param_2 << 16) >> 28;
        b = c;
        if ((c != 0) || (i == 3) || (i == 1)) f = 0;
        param_2 = param_2 << 4; i = i + 1;
        t = *(unsigned short *)(base + 0x1e);
        *(unsigned short *)(base + 0x1e) = f | (t & ~0x100);
        base[0x20] = b * 8 + 8;
        base = base + 0x14;
    } while (i < 4);
}
#endif
