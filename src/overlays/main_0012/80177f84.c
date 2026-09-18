/* Overlay range [80177F84,80178004) from MAIN.CD member 0012.
 * SHA256(span)=bed8f3b04b51ef580ed5ea79d423f6ed955c6b21d88e5e6043358e88815c0ce0.
 * Word export for the native seam; the C body below is kept
 * byte-identical (wrap only, no rewrite): the cleaned Druthulu/BFM-decomp
 * form (vendor/bfm-decomp, same SLUS-00726 build), re-verified against
 * retail at the recorded optimization by tools/match_function.py. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24080100)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x240A0005)
MUSASHI_NATIVE_MIPS_WORD(0x2409FEFF)
MUSASHI_NATIVE_MIPS_WORD(0x2486000C)
MUSASHI_NATIVE_MIPS_WORD(0x00051403)
MUSASHI_NATIVE_MIPS_WORD(0x3042000F)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00402021)
MUSASHI_NATIVE_MIPS_WORD(0x00071400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x104A0003)
MUSASHI_NATIVE_MIPS_WORD(0x00052900)
MUSASHI_NATIVE_MIPS_WORD(0x10800002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x24C60014)
MUSASHI_NATIVE_MIPS_WORD(0x24E20001)
MUSASHI_NATIVE_MIPS_WORD(0x00403821)
MUSASHI_NATIVE_MIPS_WORD(0x000318C0)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x94C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x28420005)
MUSASHI_NATIVE_MIPS_WORD(0xA0C30000)
MUSASHI_NATIVE_MIPS_WORD(0x00892024)
MUSASHI_NATIVE_MIPS_WORD(0x01042025)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE8)
MUSASHI_NATIVE_MIPS_WORD(0xA4C4FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* func_80177F84 - 32 words. Promoted from vendor/bfm-decomp
 * (Druthulu, same SLUS-00726 build), split to an address-named file.
 * Values and locals are the loosest that reproduce the bytes; they
 * are not evidence of the original declaration. */


void func_80177F84(s32 param_1, s32 param_2) {
    u16 uVar4;
    s16 iVar3;
    register u8 *pcVar2 __asm__("$6");
    u32 uVar1;
    register s32 c5 __asm__("$10");
    register s32 cmask __asm__("$9");
    uVar4 = 0x100;
    iVar3 = 0;
    c5 = 5;
    cmask = -257;
    pcVar2 = (u8 *)(param_1 + 0xc);
    do {
        register u32 src __asm__("$2");
        register u32 byteval __asm__("$3");
        register u32 testval __asm__("$4");
        src = (param_2 >> 0x10) & 0xf;
        __asm__ __volatile__("" : : "r"(src));
        byteval = src;
        __asm__ __volatile__("" : "=r"(byteval) : "0"(byteval));
        testval = src;
        __asm__ __volatile__("" : : "r"(byteval), "r"(testval));
        param_2 = param_2 << 4;
        if ((iVar3 == c5) || (testval != 0)) {
            uVar4 = 0;
        }
        pcVar2 += 0x14;
        iVar3 += 1;
        {
            register s32 r __asm__("$4");
            r = *(u16 *)(pcVar2 - 2);
            pcVar2[0] = (u8)(byteval * 8 + 8);
            *(u16 *)(pcVar2 - 2) = uVar4 | (r & cmask);
        }
    } while (iVar3 < 5);
}
#endif
