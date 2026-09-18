/* Overlay range [8013F1BC,8013F244) from MAIN.CD member 0012.
 * SHA256(span)=e83706c5b7ed6054f55030692fbcfb72277de70db4baf2ca36a4736451b04d7c.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x24635118)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFF0)
MUSASHI_NATIVE_MIPS_WORD(0xA4620000)
MUSASHI_NATIVE_MIPS_WORD(0x94620000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400012)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x94429A02)
MUSASHI_NATIVE_MIPS_WORD(0x3C038011)
MUSASHI_NATIVE_MIPS_WORD(0x94635114)
MUSASHI_NATIVE_MIPS_WORD(0x38420001)
MUSASHI_NATIVE_MIPS_WORD(0x14620005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C034989)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804FC8D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x94425112)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA4225112)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_8013F1BC - 34 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */
extern void func_800D2624(void);
extern short D_800B9A02;
extern unsigned short D_80115114;
extern unsigned short D_80115112;
extern unsigned short D_80115118;

void func_8013F1BC(void) {
    unsigned short *p = &D_80115118;
    if (*p != 0) {
        *p -= 0x10;
        __asm__ __volatile__("" ::: "memory");
        if (*p != 0) {
            return;
        }
    }
    if (D_80115114 == ((unsigned short)D_800B9A02 ^ 1)) {
        func_800D2624();
    } else {
        D_80115112 += 1;
    }
}
#endif
