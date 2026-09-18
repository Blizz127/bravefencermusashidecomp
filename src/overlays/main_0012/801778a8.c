/* Overlay range [801778A8,80177940) from MAIN.CD member 0012.
 * SHA256(span)=8b5bbfd874d7c4d1ca0c1afe2039f0076689b0c3f3013e36287db414732d5062.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24090100)
MUSASHI_NATIVE_MIPS_WORD(0x00063400)
MUSASHI_NATIVE_MIPS_WORD(0x00063403)
MUSASHI_NATIVE_MIPS_WORD(0x18C00020)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x24CBFFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00025403)
MUSASHI_NATIVE_MIPS_WORD(0x240CFEFF)
MUSASHI_NATIVE_MIPS_WORD(0x2487000C)
MUSASHI_NATIVE_MIPS_WORD(0x00051400)
MUSASHI_NATIVE_MIPS_WORD(0x00021702)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00081400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104B0003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x144A0002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00004821)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x25020001)
MUSASHI_NATIVE_MIPS_WORD(0x00404021)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94E4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x0046102A)
MUSASHI_NATIVE_MIPS_WORD(0xA0E30000)
MUSASHI_NATIVE_MIPS_WORD(0x008C2024)
MUSASHI_NATIVE_MIPS_WORD(0x01242025)
MUSASHI_NATIVE_MIPS_WORD(0xA4E4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE7)
MUSASHI_NATIVE_MIPS_WORD(0x24E70014)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_801778A8 - 38 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_801778A8(int param_1, unsigned int param_2, short param_3, short param_4) {
    register unsigned int uVar1 __asm__("$2");
    register unsigned int nib __asm__("$3");
    int iVar2;
    register int im1 __asm__("$11");
    int p4;
    register char *p __asm__("$7");
    short iVar4;
    unsigned short uVar5;
    register unsigned int mask __asm__("$12");
    uVar5 = 0x100;
    iVar2 = (int)param_3;
    iVar4 = 0;
    if (0 < iVar2) {
        im1 = iVar2 - 1;
        p4 = (int)param_4;
        mask = ~0x100;
        p = (char *)(param_1 + 0xc);
        do {
            uVar1 = (param_2 << 16) >> 28;
            nib = uVar1;
            if (((uVar1 != 0) || ((int)iVar4 == im1)) ||
                ((int)iVar4 == p4)) {
                uVar5 = 0;
            }
            param_2 = param_2 << 4;
            *p = (char)(nib * 8 + 8);
            *(unsigned short *)(p - 2) = uVar5 | (*(unsigned short *)(p - 2) & mask);
            iVar4 = iVar4 + 1;
            p = p + 0x14;
        } while ((int)iVar4 < iVar2);
    }
    return;
}
#endif
